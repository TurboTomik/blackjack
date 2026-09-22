#include "ui.h"
#include "game.h"
#include "layout.h"
#include "ui_header.h"
#include "ui_key_hints.h"
#include "ui_notification.h"
#include "ui_playground.h"
#include <ncurses.h>

void render_game(const GameState *game) {
  erase();
  wnoutrefresh(stdscr);

  render_header(game->layout.header, game->money, game->bet);
  render_key_hints(game->layout.bottom, game->phase);

  switch (game->phase) {
  case STATE_BETTING:
    break;

  case STATE_PLAYER_TURN:
    render_playground(game, 1);
    break;

  case STATE_DEALER_TURN:
    render_playground(game, 0);
    break;
  case STATE_FINISHED:
    break;

  case STATE_NOTIFICATION:
    render_playground(game, 0);
    render_notification(game->layout.popup, game->active_notification);
    break;
  }

  doupdate();
}

void resize_game(GameState *game) {
  init_layout(&game->layout);
  render_game(game);
}
