#include "game.h"
#include "hand.h"
#include "ui_header.h"
#include "ui_playground.h"
#include <ncurses.h>
#include <string.h>

static void reset_hand(Hand *hand) { memset(hand, 0, sizeof *hand); }

void bet_increase(unsigned *bet) {
  if (*bet + STEP_BET > MAX_BET)
    *bet = MAX_BET;
  else
    *bet += STEP_BET;
}

void bet_decrease(unsigned *bet) {
  if (*bet - STEP_BET < MIN_BET)
    *bet = MIN_BET;
  else
    *bet -= STEP_BET;
}

static GameResult determine_winner(const GameState *game) {
  if (is_bust(&game->player))
    return RESULT_DEALER_WIN;
  if (is_bust(&game->dealer))
    return RESULT_PLAYER_WIN;
  if (game->player.score > game->dealer.score)
    return RESULT_PLAYER_WIN;
  if (game->dealer.score > game->player.score)
    return RESULT_DEALER_WIN;
  return RESULT_PUSH;
}

static void apply_result(GameState *game, GameResult result) {
  switch (result) {
  case RESULT_PLAYER_WIN:
    game->money += game->bet;
    break;
  case RESULT_DEALER_WIN:
    game->money -= game->bet;
    break;
  case RESULT_PUSH:
    break;
  }
}

void dealer_turn(GameState *game) {
  calculate_hand_score(&game->dealer);
  while (game->dealer.score < DEALER_STAND &&
         deal_to_hand(&game->deck, &game->dealer))
    calculate_hand_score(&game->dealer);

  draw_playground(game);
  doupdate();
}

void init_game_state(GameState *game, unsigned int starting_money,
                     unsigned int starting_bet) {
  memset(game, 0, sizeof *game);
  game->money = starting_money;
  game->bet = starting_bet;
  game->phase = STATE_BETTING;
}

void begin_round(GameState *game) {
  game->phase = STATE_PLAYING;

  reset_hand(&game->dealer);
  reset_hand(&game->player);

  build_deck(&game->deck);
  shuffle_deck(&game->deck);

  deal_to_hand(&game->deck, &game->dealer);
  deal_to_hand(&game->deck, &game->dealer);
  deal_to_hand(&game->deck, &game->player);
  deal_to_hand(&game->deck, &game->player);

  calculate_hand_score(&game->dealer);
  calculate_hand_score(&game->player);

  draw_playground(game);
  doupdate();
}

static void round_over(GameState *game) {
  erase();
  draw_header(game->money, game->bet);
  wnoutrefresh(stdscr);
  doupdate();

  game->phase = STATE_BETTING;
}

void finish_round(GameState *game) {
  GameResult result = determine_winner(game);
  apply_result(game, result);

  game->phase = STATE_ROUND_OVER;
  draw_playground(game);
  display_result(result);

  round_over(game);
}
