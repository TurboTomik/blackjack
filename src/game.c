#include "game.h"
#include <string.h>

void init_game_state(GameState *game, const unsigned int starting_money,
                     const unsigned int starting_bet) {
  memset(game, 0, sizeof *game);
  game->money = starting_money;
  game->bet = starting_bet;
}

void change_game_phase(GameState *game, const GamePhase new_phase) {
  game->previous_phase = game->phase;
  game->phase = new_phase;
}

void start_betting(GameState *game) {
  if (game->bet > game->money) {
    game->bet = game->money;
  }
  change_game_phase(game, STATE_BETTING);
}

void trigger_notification(GameState *game, NotificationType type) {
  game->active_notification = type;
}

void dismiss_notification(GameState *game) {
  game->active_notification = NOTIF_NONE;
}
