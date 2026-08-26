#ifndef RESULT_H
#define RESULT_H

#include "hand.h"

#define BLACKJACK_COEFFICIENT 1.5

typedef enum {
  RESULT_PLAYER_WIN,
  RESULT_DEALER_WIN,
  RESULT_BLACKJACK,
  RESULT_PUSH
} GameResult;

GameResult determine_winner(Hand *dealer_hand, Hand *player_hand);
void apply_result(unsigned *money, unsigned bet, GameResult result);

#endif // !RESULT_H
