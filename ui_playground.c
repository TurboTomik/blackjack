#include "ui_playground.h"
#include "game.h"
#include "ui_card.h"
#include "ui_notification.h"
#include <ncurses.h>
#include <string.h>

WINDOW *draw_playground(const GameState *game) {
  static WINDOW *playground = NULL;
  static HandRenderer dealer_renderer = {0};
  static HandRenderer player_renderer = {0};

  if (!playground)
    playground = newwin(getmaxy(stdscr) - PLAYGROUND_MARGIN_BOT,
                        getmaxx(stdscr), PLAYGROUND_BEGIN_LINE, 0);
  else
    werase(playground);

  int hide_dealer_hole = (game->phase == STATE_PLAYING);

  draw_hand_cards(&dealer_renderer, playground, &game->dealer,
                  DEALER_LABEL_LINE + 1, hide_dealer_hole);
  mvwprintw(playground, DEALER_LABEL_LINE,
            getmaxx(playground) / 2 - strlen(DEALER_LABEL) / 2, "%s",
            DEALER_LABEL);
  if (hide_dealer_hole && game->dealer.count > 1) {
    int visible_value = card_value(game->dealer.cards[1].rank);
    mvwprintw(playground, DEALER_SCORE_LINE, getmaxx(playground) / 2 - 5,
              "%2d points", visible_value);
  } else {
    mvwprintw(playground, DEALER_SCORE_LINE, getmaxx(playground) / 2 - 5,
              "%2d points", game->dealer.score);
  }

  draw_hand_cards(&player_renderer, playground, &game->player,
                  PLAYER_LABEL_LINE + 1, 0);
  mvwprintw(playground, PLAYER_LABEL_LINE,
            getmaxx(playground) / 2 - strlen(PLAYER_LABEL) / 2, "%s",
            PLAYER_LABEL);
  mvwprintw(playground, PLAYER_SCORE_LINE, getmaxx(playground) / 2 - 5,
            "%2d points", game->player.score);

  wnoutrefresh(playground);
  return playground;
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
