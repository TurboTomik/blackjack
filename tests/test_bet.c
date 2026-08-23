#include "bet.h"
#include "test.h"

#include <assert.h>

static void test_bet_increase_normal(void) {
  unsigned bet = 100;

  bet_increase(&bet);

  CHECK_EQ(bet, 100 + STEP_BET);
}

static void test_bet_increase_to_max(void) {
  unsigned bet = MAX_BET - STEP_BET;

  bet_increase(&bet);

  CHECK_EQ(bet, MAX_BET);
}

static void test_bet_increase_at_max(void) {
  unsigned bet = MAX_BET;

  bet_increase(&bet);

  CHECK_EQ(bet, MAX_BET);
}

static void test_bet_increase_above_max(void) {
  unsigned bet = MAX_BET + 1;

  bet_increase(&bet);

  CHECK_EQ(bet, MAX_BET);
}

static void test_bet_decrease_normal(void) {
  unsigned bet = 100;

  bet_decrease(&bet);

  CHECK_EQ(bet, 100 - STEP_BET);
}

static void test_bet_decrease_to_min(void) {
  unsigned bet = MIN_BET + STEP_BET;

  bet_decrease(&bet);

  CHECK_EQ(bet, MIN_BET);
}

static void test_bet_decrease_at_min(void) {
  unsigned bet = MIN_BET;

  bet_decrease(&bet);

  CHECK_EQ(bet, MIN_BET);
}

static void test_bet_decrease_below_min(void) {
  unsigned bet = MIN_BET - 1;

  bet_decrease(&bet);

  CHECK_EQ(bet, MIN_BET);
}

void run_bet_tests(void) {
  RUN_TEST(test_bet_increase_normal);
  RUN_TEST(test_bet_increase_to_max);
  RUN_TEST(test_bet_increase_at_max);
  RUN_TEST(test_bet_increase_above_max);

  RUN_TEST(test_bet_decrease_normal);
  RUN_TEST(test_bet_decrease_to_min);
  RUN_TEST(test_bet_decrease_at_min);
  RUN_TEST(test_bet_decrease_below_min);
}
