#ifndef GAME_H
#define GAME_H

#include "hand.h"

#define INIT_MONEY 200
#define MIN_BET 50
#define MAX_BET MIN_BET * 5
#define STEP_BET 5

#define DEALER_STAND 17

typedef enum
{
  STATE_BETTING,
  STATE_PLAYING,
  STATE_ROUND_OVER,
} GamePhase;

typedef struct
{
  Deck deck;

  Hand dealer;
  Hand player;

  unsigned money;
  unsigned bet;

  GamePhase phase;
} GameState;

typedef enum
{
  RESULT_PLAYER_WIN,
  RESULT_DEALER_WIN,
  RESULT_PUSH
} GameResult;

void bet_increase (unsigned *bet);
void bet_decrease (unsigned *bet);
void init_game_state (GameState *game, unsigned int starting_money,
                      unsigned int starting_bet);
void begin_round (GameState *game);
void handle_player_input (GameState *game, int ch);

#endif // !GAME_H
