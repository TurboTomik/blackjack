#include "bet.h"
#include "game.h"
#include "input.h"
#include "round.h"
#include "test.h"

#include <ncurses.h>
#include <string.h>

static GameState game;

static void setup_game(unsigned int money, unsigned int bet) {
  memset(&game, 0, sizeof(GameState));
  init_game_state(&game, money, bet);
}

static void test_betting_input_increase(void) {
  setup_game(1000, MIN_BET);

  handle_betting_input(&game, KEY_UP);

  CHECK_EQ(game.bet, MIN_BET + STEP_BET);
}

static void test_betting_input_decrease(void) {
  setup_game(1000, MIN_BET + STEP_BET);

  handle_betting_input(&game, KEY_DOWN);

  CHECK_EQ(game.bet, MIN_BET);
}

static void test_betting_input_min_limit(void) {
  setup_game(1000, MIN_BET);

  handle_betting_input(&game, KEY_DOWN);

  CHECK_EQ(game.bet, MIN_BET);
}

static void test_betting_input_max_bet_limit(void) {
  setup_game(1000, MAX_BET);

  handle_betting_input(&game, KEY_UP);

  CHECK_EQ(game.bet, MAX_BET);
}

static void test_betting_input_start_round_valid(void) {
  setup_game(1000, MIN_BET);

  handle_betting_input(&game, '\n');

  CHECK_EQ(game.phase, STATE_PLAYER_TURN);
  CHECK_EQ(game.player.count, 2);
  CHECK_EQ(game.dealer.count, 2);
}

static void test_betting_input_ignored_key(void) {
  setup_game(1000, MIN_BET);

  handle_betting_input(&game, 'z');

  CHECK_EQ(game.bet, MIN_BET);
  CHECK_EQ(game.phase, STATE_BETTING);
}

static void test_player_input_hit_adds_card(void) {
  setup_game(1000, MIN_BET);
  begin_round(&game);

  game.player.score = 10;
  game.phase = STATE_PLAYER_TURN;
  uint8_t count_before = game.player.count;

  handle_player_input(&game, 'h');

  CHECK_EQ(game.player.count, (unsigned int)count_before + 1);
  CHECK(game.player.score > 10);
}

static void test_player_input_stand_finishes_turn(void) {
  setup_game(1000, MIN_BET);
  begin_round(&game);

  handle_player_input(&game, ' ');

  CHECK_EQ(game.phase, STATE_NOTIFICATION);
  CHECK(game.dealer.score >= 17 || is_bust(&game.dealer));
}

static void test_player_input_double_success(void) {
  setup_game(1000, MIN_BET);
  begin_round(&game);

  handle_player_input(&game, 'd');

  CHECK_EQ(game.bet, MIN_BET * 2);
  CHECK_EQ(game.player.count, 3);
  CHECK_EQ(game.phase, STATE_NOTIFICATION);
}

static void test_player_input_double_insufficient_funds(void) {
  setup_game(60, 50); // Недостаточно средств для двойной ставки 100
  begin_round(&game);

  handle_player_input(&game, 'd');

  CHECK_EQ(game.bet, 50);
  CHECK_EQ(game.player.count, 2);
  CHECK_EQ(game.phase, STATE_PLAYER_TURN);
}

static void test_result_input_dismiss(void) {
  setup_game(1000, MIN_BET);
  game.phase = STATE_NOTIFICATION;
  game.previous_phase = STATE_BETTING;
  game.active_notification = NOTIF_RESULT_PLAYER_WIN;

  handle_result_input(&game, 'a');

  CHECK_EQ(game.phase, STATE_BETTING);
  CHECK_EQ(game.active_notification, NOTIF_NONE);
}

void run_input_tests(void) {
  RUN_TEST(test_betting_input_increase);
  RUN_TEST(test_betting_input_decrease);
  RUN_TEST(test_betting_input_min_limit);
  RUN_TEST(test_betting_input_max_bet_limit);
  RUN_TEST(test_betting_input_start_round_valid);
  RUN_TEST(test_betting_input_ignored_key);

  RUN_TEST(test_player_input_hit_adds_card);
  RUN_TEST(test_player_input_stand_finishes_turn);
  RUN_TEST(test_player_input_double_success);
  RUN_TEST(test_player_input_double_insufficient_funds);

  RUN_TEST(test_result_input_dismiss);
}
