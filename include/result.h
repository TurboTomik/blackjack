#ifndef RESULT_H
#define RESULT_H

#include "hand.h"

#define BLACKJACK_COEFFICIENT 2.5

typedef enum {
  RESULT_PLAYER_WIN,
  RESULT_DEALER_WIN,
  RESULT_BLACKJACK,
  RESULT_PUSH
} GameResult;

GameResult determine_winner(const Hand *dealer_hand, const Hand *player_hand);
void apply_result(unsigned *money, unsigned bet, GameResult result);

#endif // !RESULT_H
