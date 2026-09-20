#include "round.h"
#include "game.h"
#include "hand.h"
#include "result.h"
#include "ui_notification.h"
#include <string.h>

static int can_start_round(unsigned int money, unsigned int bet) {
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

static void prepare_round(GameState *game) {
  reset_hand(&game->dealer);
  reset_hand(&game->player);

  build_deck(&game->deck);
  shuffle_deck(&game->deck);

  deal_opening_hands(game);

  calculate_hand_score(&game->dealer);
  calculate_hand_score(&game->player);
}

static void play_dealer_hand(GameState *game) {
  game->phase = STATE_DEALER_TURN;

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

static void double_down(GameState *game) {
  game->bet *= 2;
  deal_to_hand(&game->deck, &game->player);
  calculate_hand_score(&game->player);
}

void begin_round(GameState *game) {
  if (!can_start_round(game->money, game->bet)) {
    trigger_notification(game, NOTIF_INSUFFICIENT_FUNDS);
    return;
  }
  game->phase = STATE_PLAYER_TURN;
  prepare_round(game);
}

static void finish_round(GameState *game) {
  GameResult result = determine_winner(&game->dealer, &game->player);
  apply_result(&game->money, game->bet, result);

  game->phase = STATE_BETTING;

  if (result == RESULT_PLAYER_WIN || result == RESULT_BLACKJACK) {
    trigger_notification(game, NOTIF_RESULT_PLAYER_WIN);
  } else if (result == RESULT_DEALER_WIN) {
    trigger_notification(game, NOTIF_RESULT_DEALER_WIN);
  } else {
    trigger_notification(game, NOTIF_RESULT_PUSH);
  }
}
void player_hit(GameState *game) {
  if (!deal_to_hand(&game->deck, &game->player)) {
    return;
  }

  calculate_hand_score(&game->player);

  if (is_bust(&game->player)) {
    finish_round(game);
  }
}

void player_double_down(GameState *game) {
  if (!can_double_down(game->money, game->bet, game->player.count)) {
    return;
  }

  double_down(game);
  if (is_bust(&game->player)) {
    finish_round(game);
  } else {
    player_stand(game);
  }
}

void player_stand(GameState *game) {
  play_dealer_hand(game);
  finish_round(game);
}

void trigger_notification(GameState *game, NotificationType type) {
  game->active_notification = type;
  game->previous_phase = game->phase;
  game->phase = STATE_NOTIFICATION;
}

void dismiss_notification(GameState *game) {
  game->phase = game->previous_phase;
  game->active_notification = NOTIF_NONE;
}
