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
  STATE_NOTIFICATION,
} GamePhase;

typedef struct {
  Deck deck;

  Hand dealer;
  Hand player;

  unsigned money;
  unsigned bet;

  GamePhase phase;
  GamePhase previous_phase;

  GameLayout layout;

  GameResult last_result;
  NotificationType active_notification;
} GameState;

#endif // !GAME_H
