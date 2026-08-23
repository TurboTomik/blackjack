#include "card.h"
#include "test.h"

static void test_ace_is_eleven(void) { CHECK_EQ(card_value(ACE), 11); }

static void test_number_cards_match_rank(void) {
  CHECK_EQ(card_value(TWO), 2);
  CHECK_EQ(card_value(FIVE), 5);
  CHECK_EQ(card_value(NINE), 9);
}

static void test_ten_and_face_cards_are_ten(void) {
  CHECK_EQ(card_value(TEN), 10);
  CHECK_EQ(card_value(JACK), 10);
  CHECK_EQ(card_value(QUEEN), 10);
  CHECK_EQ(card_value(KING), 10);
}

void run_card_tests(void) {
  RUN_TEST(test_ace_is_eleven);
  RUN_TEST(test_number_cards_match_rank);
  RUN_TEST(test_ten_and_face_cards_are_ten);
}
