#include "round.h"
#include "game.h"
#include "hand.h"
#include <string.h>

int can_start_round(unsigned int money, unsigned int bet) {
  return bet <= money;
}

void init_game_state(GameState *game, unsigned int starting_money,
                     unsigned int starting_bet) {
  memset(game, 0, sizeof *game);
  game->money = starting_money;
  game->bet = starting_bet;
  game->phase = STATE_BETTING;
}

static void reset_hand(Hand *hand) { memset(hand, 0, sizeof *hand); }

static void deal_opening_hands(GameState *game) {
  deal_to_hand(&game->deck, &game->dealer);
  deal_to_hand(&game->deck, &game->dealer);
  deal_to_hand(&game->deck, &game->player);
  deal_to_hand(&game->deck, &game->player);
}

void start_new_round(GameState *game) {
  reset_hand(&game->dealer);
  reset_hand(&game->player);

  build_deck(&game->deck);
  shuffle_deck(&game->deck);

  deal_opening_hands(game);

  calculate_hand_score(&game->dealer);
  calculate_hand_score(&game->player);
}

void play_dealer_hand(GameState *game) {
  calculate_hand_score(&game->dealer);
  while (game->dealer.score < DEALER_STAND &&
         deal_to_hand(&game->deck, &game->dealer)) {
    calculate_hand_score(&game->dealer);
  }
}

int can_double_down(unsigned int money, unsigned int bet,
                    unsigned int player_card_count) {
  return player_card_count == 2 && can_start_round(money, bet * 2);
}

void double_down(GameState *game) {
  game->bet *= 2;
  deal_to_hand(&game->deck, &game->player);
  calculate_hand_score(&game->player);
}
