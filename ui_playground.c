#include "ui_playground.h"
#include "card.h"
#include "game.h"
#include "ui_card.h"
#include "ui_notification.h"
#include <ncurses.h>
#include <string.h>

static WINDOW *playground = NULL;
static HandRenderer dealer_renderer = {0};
static HandRenderer player_renderer = {0};

static WINDOW *get_playground_window(void) {
  if (!playground)
    playground = newwin(getmaxy(stdscr) - PLAYGROUND_MARGIN_BOT,
                        getmaxx(stdscr), PLAYGROUND_BEGIN_LINE, 0);
  else
    werase(playground);
  return playground;
}

static int dealer_visible_score(const GameState *game, int hole_hidden) {
  if (hole_hidden && game->dealer.count > 1)
    return card_value(game->dealer.cards[1].rank);
  return game->dealer.score;
}

static void draw_label(WINDOW *win, int line, const char *label) {
  mvwprintw(win, line, getmaxx(win) / 2 - strlen(label) / 2, "%s", label);
}

static void draw_score(WINDOW *win, int line, int score) {
  mvwprintw(win, line, getmaxx(win) / 2 - 5, "%2d points", score);
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

WINDOW *draw_playground(const GameState *game) {
  WINDOW *win = get_playground_window();
  int hole_hidden = (game->phase == STATE_PLAYING);

  draw_dealer_section(win, game, hole_hidden);
  draw_player_section(win, game);

  wnoutrefresh(win);
  return win;
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
