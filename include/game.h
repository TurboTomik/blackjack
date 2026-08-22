#ifndef GAME_H
#define GAME_H

#include "hand.h"

#define INIT_MONEY 200

#define DEALER_STAND 17

typedef enum {
  STATE_BETTING,
  STATE_PLAYING,
} GamePhase;

typedef struct {
  Deck deck;

  Hand dealer;
  Hand player;

  unsigned money;
  unsigned bet;

  GamePhase phase;
} GameState;

void init_game_state(GameState *game, unsigned int starting_money,
                     unsigned int starting_bet);
void dealer_turn(GameState *game);
void begin_round(GameState *game);
void finish_round(GameState *game);

#endif // !GAME_H
