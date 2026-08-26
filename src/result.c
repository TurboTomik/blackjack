#include "result.h"
#include "hand.h"

GameResult determine_winner(Hand *dealer_hand, Hand *player_hand) {
  if (is_bust(player_hand)) {
    return RESULT_DEALER_WIN;
  }
  if (is_bust(dealer_hand)) {
    return RESULT_PLAYER_WIN;
  }
  if (player_hand->score == BLACKJACK && dealer_hand->score != BLACKJACK) {
    return RESULT_BLACKJACK;
  }
  if (player_hand->score > dealer_hand->score) {
    return RESULT_PLAYER_WIN;
  }
  if (dealer_hand->score > player_hand->score) {
    return RESULT_DEALER_WIN;
  }
  return RESULT_PUSH;
}

void apply_result(unsigned *money, unsigned bet, GameResult result) {
  switch (result) {
  case RESULT_PLAYER_WIN:
    *money += bet;
    break;
  case RESULT_DEALER_WIN:
    *money -= bet;
    break;
  case RESULT_BLACKJACK:
    *money += (int)(bet * BLACKJACK_COEFFICIENT);
    break;
  case RESULT_PUSH:
    break;
  }
}
