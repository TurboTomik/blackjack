#include "input.h"

#include <ncurses.h>

#include "bet.h"
#include "game.h"
#include "round.h"
#include "ui.h"

void handle_betting_input(GameState *game, int ch) {
  switch (ch) {
  case KEY_UP:
    bet_increase(&game->bet);
    break;
  case KEY_DOWN:
    bet_decrease(&game->bet);
    break;
  case '\n':
  case ' ':
    begin_round(game);
    break;

  default:
    break;
  }
}

void handle_player_input(GameState *game, int ch) {
  switch (ch) {
  case 'h':
    player_hit(game);
    break;

  case 'd':
    player_double_down(game);
    break;

  case ' ':
    player_stand(game);
    break;

  default:
    break;
  }
}

void handle_result_input(GameState *game, int ch) {
  (void)ch;
  dismiss_notification(game);
}

void handle_resize(GameState *game) { resize_game(game); }
