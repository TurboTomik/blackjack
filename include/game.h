#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "hand.h"
#include "layout.h"
#include "result.h"
#include "ui_notification.h"

#define INIT_MONEY 200
#define DEALER_STAND 17

typedef enum {
  STATE_BETTING,
  STATE_PLAYER_TURN,
  STATE_DEALER_TURN,
  STATE_FINISHED,
} GamePhase;

typedef struct {
  Deck deck;

  Hand dealer;
  Hand player;

  unsigned money;
  unsigned bet;
  unsigned wager;

  GamePhase phase;
  GamePhase previous_phase;

  GameLayout layout;

  GameResult last_result;
  NotificationType active_notification;
} GameState;

void init_game_state(GameState *game, unsigned int starting_money,
                     unsigned int starting_bet);
void change_game_phase(GameState *game, GamePhase new_phase);
void start_betting(GameState *game);
void trigger_notification(GameState *game, NotificationType type);
void dismiss_notification(GameState *game);

#endif // !GAME_H
