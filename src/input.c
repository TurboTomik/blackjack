#include "input.h"

#include "bet.h"
#include "ui_header.h"
#include "ui_playground.h"

void handle_betting_input(GameState *game, int ch) {
  switch (ch) {
  case KEY_UP:
    bet_increase(&game->bet);
    render_bet(game->bet);
    break;
  case KEY_DOWN:
    bet_decrease(&game->bet);
    render_bet(game->bet);
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
    if (!deal_to_hand(&game->deck, &game->player)) {
      break;
    }
    calculate_hand_score(&game->player);
    render_playground(game, 1);
    if (is_bust(&game->player)) {
      finish_round(game);
    }
    break;

  case ' ':
    dealer_turn(game);
    finish_round(game);
    break;

  default:
    break;
  }
}
