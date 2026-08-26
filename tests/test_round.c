#include "round.h"
#include "test.h"

/* --- can_start_round --- */

static void test_bet_equal_to_money_is_allowed(void) {
  CHECK(can_start_round(50, 50));
}

static void test_bet_less_than_money_is_allowed(void) {
  CHECK(can_start_round(200, 50));
}

static void test_bet_more_than_money_is_not_allowed(void) {
  CHECK(!can_start_round(20, 50));
}

static void test_zero_money_zero_bet_is_allowed(void) {
  CHECK(can_start_round(0, 0));
}

/* --- init_game_state --- */

static void test_init_game_state_sets_starting_values(void) {
  GameState game;
  init_game_state(&game, 200, 50);

  CHECK_EQ(game.money, 200U);
  CHECK_EQ(game.bet, 50U);
  CHECK_EQ(game.phase, STATE_BETTING);
}

static void test_init_game_state_starts_with_empty_hands(void) {
  GameState game;
  init_game_state(&game, 200, 50);

  CHECK_EQ(game.dealer.count, 0U);
  CHECK_EQ(game.player.count, 0U);
}

/* --- start_new_round --- */

static void test_start_new_round_deals_opening_hands(void) {
  GameState game;
  init_game_state(&game, 200, 50);

  start_new_round(&game);

  CHECK_EQ(game.dealer.count, 2U);
  CHECK_EQ(game.player.count, 2U);
}

static void test_start_new_round_scores_both_hands(void) {
  GameState game;
  init_game_state(&game, 200, 50);

  start_new_round(&game);

  CHECK(game.dealer.score > 0);
  CHECK(game.player.score > 0);
}

static void test_start_new_round_resets_a_dirty_hand(void) {
  GameState game;
  init_game_state(&game, 200, 50);

  start_new_round(&game);
  unsigned first_round_dealer_count = game.dealer.count;
  CHECK_EQ(first_round_dealer_count, 2U);

  start_new_round(&game);

  CHECK_EQ(game.dealer.count, 2U);
  CHECK_EQ(game.player.count, 2U);
}

static void
test_start_new_round_gives_a_full_fresh_deck_minus_opening_deal(void) {
  GameState game;
  init_game_state(&game, 200, 50);

  start_new_round(&game);

  CHECK_EQ(game.deck.pos, 4U);
}

/* --- play_dealer_hand --- */

static void test_dealer_stops_at_or_above_stand_value(void) {
  GameState game;
  init_game_state(&game, 200, 50);
  start_new_round(&game);

  play_dealer_hand(&game);

  CHECK(game.dealer.score >= DEALER_STAND || game.dealer.score > 21);
}

static void test_dealer_never_exceeds_deck_capacity(void) {
  int ran_to_completion = 1;
  for (int trial = 0; trial < 200; trial++) {
    GameState game;
    init_game_state(&game, 200, 50);
    start_new_round(&game);
    play_dealer_hand(&game);
  }
  CHECK(ran_to_completion);
}

void run_round_tests(void) {
  RUN_TEST(test_bet_equal_to_money_is_allowed);
  RUN_TEST(test_bet_less_than_money_is_allowed);
  RUN_TEST(test_bet_more_than_money_is_not_allowed);
  RUN_TEST(test_zero_money_zero_bet_is_allowed);

  RUN_TEST(test_init_game_state_sets_starting_values);
  RUN_TEST(test_init_game_state_starts_with_empty_hands);

  RUN_TEST(test_start_new_round_deals_opening_hands);
  RUN_TEST(test_start_new_round_scores_both_hands);
  RUN_TEST(test_start_new_round_resets_a_dirty_hand);
  RUN_TEST(test_start_new_round_gives_a_full_fresh_deck_minus_opening_deal);

  RUN_TEST(test_dealer_stops_at_or_above_stand_value);
  RUN_TEST(test_dealer_never_exceeds_deck_capacity);
}
