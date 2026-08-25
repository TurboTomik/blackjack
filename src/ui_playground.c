#include "ui_playground.h"
#include "card.h"
#include "ui_card.h"
#include "ui_notification.h"
#include <ncurses.h>
#include <string.h>

static WINDOW *playground = NULL;
static HandRenderer dealer_renderer = {0};
static HandRenderer player_renderer = {0};

static WINDOW *get_playground_window(void) {
  if (!playground) {
    playground = newwin(getmaxy(stdscr) - PLAYGROUND_MARGIN_BOT,
                        getmaxx(stdscr), PLAYGROUND_BEGIN_LINE, 0);
  } else {
    werase(playground);
  }
  return playground;
}

static unsigned dealer_visible_score(const GameState *game, int hole_hidden) {
  if (hole_hidden && game->dealer.count > 1) {
    return card_value(game->dealer.cards[1].rank);
  }
  return game->dealer.score;
}

static void draw_label(WINDOW *win, int line, const char *label) {
  int x = (getmaxx(win) / 2) - (int)(strlen(label) / 2);

  mvwprintw(win, line, x, "%s", label);
}

static void draw_score(WINDOW *win, int line, unsigned score) {
  enum { SCORE_TEXT_SIZE = 32 };
  char buf[SCORE_TEXT_SIZE];
  snprintf(buf, sizeof buf, "%2d points", score);
  int x = (getmaxx(win) / 2) - (int)(strlen(buf) / 2);

  mvwprintw(win, line, x, "%s", buf);
}

static void draw_dealer_section(WINDOW *win, const GameState *game,
                                int hole_hidden) {
  draw_label(win, DEALER_LABEL_LINE, DEALER_LABEL);
  draw_hand_cards(&dealer_renderer, win, &game->dealer, DEALER_LABEL_LINE + 1,
                  hole_hidden);
  draw_score(win, DEALER_SCORE_LINE, dealer_visible_score(game, hole_hidden));
}

static void draw_player_section(WINDOW *win, const GameState *game) {
  draw_label(win, PLAYER_LABEL_LINE, PLAYER_LABEL);
  draw_hand_cards(&player_renderer, win, &game->player, PLAYER_LABEL_LINE + 1,
                  0);
  draw_score(win, PLAYER_SCORE_LINE, game->player.score);
}

void render_playground(const GameState *game, int hide_dealer_hole) {
  WINDOW *win = get_playground_window();

  draw_dealer_section(win, game, hide_dealer_hole);
  draw_player_section(win, game);

  wnoutrefresh(win);
  doupdate();
}

void display_result(GameResult result) {
  const char *msg;
  switch (result) {
  case RESULT_PLAYER_WIN:
    msg = "You win!";
    break;
  case RESULT_DEALER_WIN:
    msg = "Dealer wins.";
    break;
  case RESULT_PUSH:
    msg = "Push.";
    break;
  default:
    msg = "";
  }
  display_notification(msg);
  wnoutrefresh(stdscr);
}
