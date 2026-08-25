#include "hand.h"
#include "result.h"
#include "test.h"
#include <string.h>

static Hand hand_with_score(unsigned score) {
  Hand hand;
  memset(&hand, 0, sizeof hand);
  hand.score = score;
  return hand;
}

static void test_player_bust_is_dealer_win(void) {
  Hand dealer = hand_with_score(18);
  Hand player = hand_with_score(22);

  CHECK_EQ(determine_winner(&dealer, &player), RESULT_DEALER_WIN);
}

static void test_player_bust_beats_dealer_bust(void) {
  /* If the player already busted, it doesn't matter that the dealer also
     busted -- the player's own hand is checked first. */
  Hand dealer = hand_with_score(24);
  Hand player = hand_with_score(22);

  CHECK_EQ(determine_winner(&dealer, &player), RESULT_DEALER_WIN);
}

static void test_dealer_bust_is_player_win(void) {
  Hand dealer = hand_with_score(23);
  Hand player = hand_with_score(18);

  CHECK_EQ(determine_winner(&dealer, &player), RESULT_PLAYER_WIN);
}

static void test_higher_score_wins(void) {
  Hand dealer = hand_with_score(17);
  Hand player = hand_with_score(20);
  CHECK_EQ(determine_winner(&dealer, &player), RESULT_PLAYER_WIN);

  dealer = hand_with_score(20);
  player = hand_with_score(17);
  CHECK_EQ(determine_winner(&dealer, &player), RESULT_DEALER_WIN);
}

static void test_equal_scores_are_a_push(void) {
  Hand dealer = hand_with_score(19);
  Hand player = hand_with_score(19);

  CHECK_EQ(determine_winner(&dealer, &player), RESULT_PUSH);
}

static void test_apply_result_player_win_adds_bet(void) {
  unsigned money = 200;
  apply_result(&money, 50, RESULT_PLAYER_WIN);
  CHECK_EQ(money, 250U);
}

static void test_apply_result_dealer_win_subtracts_bet(void) {
  unsigned money = 200;
  apply_result(&money, 50, RESULT_DEALER_WIN);
  CHECK_EQ(money, 150U);
}

static void test_apply_result_push_leaves_money_unchanged(void) {
  unsigned money = 200;
  apply_result(&money, 50, RESULT_PUSH);
  CHECK_EQ(money, 200U);
}

/* KNOWN ISSUE, documented rather than silently accepted: apply_result()
   subtracts directly into an unsigned. If a loss is ever applied with
   bet > money, this wraps around to a huge number instead of clamping at
   0. Not currently reachable through normal play (nothing stops betting
   more than you have, so it actually *is* reachable once money drops
   below MIN_BET) -- flagging this so it doesn't get lost. */
static void test_apply_result_dealer_win_underflows_if_bet_exceeds_money(void) {
  unsigned money = 20;
  apply_result(&money, 50, RESULT_DEALER_WIN);

  CHECK(money > 20U); /* wrapped around instead of going negative/zero */
}

void run_result_tests(void) {
  RUN_TEST(test_player_bust_is_dealer_win);
  RUN_TEST(test_player_bust_beats_dealer_bust);
  RUN_TEST(test_dealer_bust_is_player_win);
  RUN_TEST(test_higher_score_wins);
  RUN_TEST(test_equal_scores_are_a_push);
  RUN_TEST(test_apply_result_player_win_adds_bet);
  RUN_TEST(test_apply_result_dealer_win_subtracts_bet);
  RUN_TEST(test_apply_result_push_leaves_money_unchanged);
  RUN_TEST(test_apply_result_dealer_win_underflows_if_bet_exceeds_money);
}
