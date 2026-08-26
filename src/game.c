#include "game.h"
#include "result.h"
#include "round.h"
#include "ui_header.h"
#include "ui_playground.h"
#include <ncurses.h>

void begin_round(GameState *game) {
  game->phase = STATE_PLAYING;
  start_new_round(game);
  render_playground(game, 1);
}

void dealer_turn(GameState *game) {
  play_dealer_hand(game);
  render_playground(game, 0);
}

void finish_round(GameState *game) {
  GameResult result = determine_winner(&game->dealer, &game->player);
  apply_result(&game->money, game->bet, result);

  render_playground(game, 0);
  display_result(result);

  game->phase = STATE_BETTING;
  erase();
  render_header(game->money, game->bet);
}
