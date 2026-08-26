#include <stdio.h>

int tests_run = 0;
int tests_failed = 0;

void run_card_tests(void);
void run_deck_tests(void);
void run_hand_tests(void);
void run_bet_tests(void);
void run_result_tests(void);
void run_round_tests(void);

int main(void) {
  run_card_tests();
  run_deck_tests();
  run_hand_tests();
  run_bet_tests();
  run_result_tests();
  run_round_tests();

  printf("\n%d/%d tests passed\n", tests_run - tests_failed, tests_run);
  return tests_failed ? 1 : 0;
}
