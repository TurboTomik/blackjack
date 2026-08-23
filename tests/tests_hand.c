#include "card.h"
#include "deck.h"
#include "hand.h"
#include "test.h"
#include <string.h>

static Hand fresh_hand(void) {
  Hand hand;
  memset(&hand, 0, sizeof hand);
  return hand;
}

static void add_card(Hand *hand, Rank rank, Suit suit) {
  hand->cards[hand->count].rank = rank;
  hand->cards[hand->count].suit = suit;
  hand->count++;
}

static void test_deal_to_hand_adds_the_dealt_card(void) {
  Deck deck;
  build_deck(&deck);
  shuffle_deck(&deck);
  Hand hand = fresh_hand();

  int ok = deal_to_hand(&deck, &hand);

  CHECK_EQ(ok, 1);
  CHECK_EQ(hand.count, 1u);
  CHECK_EQ(hand.cards[0].rank, deck.cards[0].rank);
  CHECK_EQ(hand.cards[0].suit, deck.cards[0].suit);
}

static void test_deal_to_hand_stops_at_max_size(void) {
  Deck deck;
  build_deck(&deck);
  shuffle_deck(&deck);
  Hand hand = fresh_hand();

  for (int i = 0; i < MAX_HAND_SIZE; i++)
    CHECK_EQ(deal_to_hand(&deck, &hand), 1);

  CHECK_EQ(hand.count, (unsigned)MAX_HAND_SIZE);

  /* Deck still has cards left (52 - 12), but the hand is full. */
  CHECK_EQ(deal_to_hand(&deck, &hand), 0);
  CHECK_EQ(hand.count, (unsigned)MAX_HAND_SIZE);
}

static void test_deal_to_hand_fails_on_empty_deck(void) {
  Deck deck;
  build_deck(&deck);
  shuffle_deck(&deck);
  deck.pos = DECK_SIZE; /* simulate an exhausted deck */
  Hand hand = fresh_hand();

  CHECK_EQ(deal_to_hand(&deck, &hand), 0);
  CHECK_EQ(hand.count, 0u);
}

static void test_score_simple_hand(void) {
  Hand hand = fresh_hand();
  add_card(&hand, FIVE, HEARTS);
  add_card(&hand, SEVEN, CLUBS);

  CHECK_EQ(calculate_hand_score(&hand), 12);
  CHECK_EQ(hand.score, 12u);
}

static void test_ace_counts_as_eleven_when_it_fits(void) {
  Hand hand = fresh_hand();
  add_card(&hand, ACE, HEARTS);
  add_card(&hand, KING, SPADES);

  CHECK_EQ(calculate_hand_score(&hand), 21); /* natural blackjack */
}

static void test_ace_drops_to_one_to_avoid_busting(void) {
  Hand hand = fresh_hand();
  add_card(&hand, ACE, HEARTS);
  add_card(&hand, ACE, CLUBS);
  add_card(&hand, NINE, SPADES);

  /* 11 + 11 + 9 = 31 -> drop one ace to 1 -> 21 */
  CHECK_EQ(calculate_hand_score(&hand), 21);
}

static void test_multiple_aces_all_drop_if_needed(void) {
  Hand hand = fresh_hand();
  add_card(&hand, ACE, HEARTS);
  add_card(&hand, ACE, CLUBS);
  add_card(&hand, ACE, DIAMONDS);
  add_card(&hand, NINE, SPADES);

  /* Every ace-as-11 combination busts except all-as-1: 1+1+1+9 = 12 */
  CHECK_EQ(calculate_hand_score(&hand), 12);
}

static void test_is_bust_true_above_21(void) {
  Hand hand = fresh_hand();
  hand.score = 22;
  CHECK(is_bust(&hand));
}

static void test_is_bust_false_at_exactly_21(void) {
  Hand hand = fresh_hand();
  hand.score = 21;
  CHECK(!is_bust(&hand));
}

static void test_is_bust_false_below_21(void) {
  Hand hand = fresh_hand();
  hand.score = 10;
  CHECK(!is_bust(&hand));
}

void run_hand_tests(void) {
  RUN_TEST(test_deal_to_hand_adds_the_dealt_card);
  RUN_TEST(test_deal_to_hand_stops_at_max_size);
  RUN_TEST(test_deal_to_hand_fails_on_empty_deck);
  RUN_TEST(test_score_simple_hand);
  RUN_TEST(test_ace_counts_as_eleven_when_it_fits);
  RUN_TEST(test_ace_drops_to_one_to_avoid_busting);
  RUN_TEST(test_multiple_aces_all_drop_if_needed);
  RUN_TEST(test_is_bust_true_above_21);
  RUN_TEST(test_is_bust_false_at_exactly_21);
  RUN_TEST(test_is_bust_false_below_21);
}
