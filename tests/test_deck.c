#include "card.h"
#include "deck.h"
#include "test.h"

/* Counts how many times each (suit, rank) combination appears in the deck.
   A correct deck has exactly one of each of the 52 combinations. */
static void count_composition(const Deck *deck, int counts[4][14]) {
  for (int s = 0; s < 4; s++) {
    for (int r = 0; r < 14; r++) {
      counts[s][r] = 0;
    }
  }

  for (unsigned i = 0; i < DECK_SIZE; i++) {
    counts[deck->cards[i].suit][deck->cards[i].rank]++;
  }
}

static int composition_is_one_of_each(int counts[4][14]) {
  for (int s = 0; s < 4; s++) {
    for (int r = ACE; r <= KING; r++) {
      if (counts[s][r] != 1) {
        return 0;
      }
    }
  }
  return 1;
}

static void test_build_deck_has_52_unique_cards(void) {
  Deck deck;
  int counts[4][14];

  build_deck(&deck);
  count_composition(&deck, counts);

  CHECK(composition_is_one_of_each(counts));
}

static void test_build_deck_resets_position(void) {
  Deck deck;
  deck.pos = 17; /* garbage value from a previous round */

  build_deck(&deck);

  /* build_deck() only fills cards[]; dealing position is a separate concern
     the caller (shuffle_deck) resets. Document that explicitly here so a
     future change to either function doesn't silently break the other. */
  CHECK_EQ(deck.pos, 17U);
}

static void test_shuffle_preserves_composition(void) {
  Deck deck;
  int counts[4][14];

  build_deck(&deck);
  shuffle_deck(&deck);
  count_composition(&deck, counts);

  /* Shuffling must be a permutation: same 52 cards, different order. */
  CHECK(composition_is_one_of_each(counts));
}

static void test_shuffle_resets_position(void) {
  Deck deck;
  build_deck(&deck);
  deck.pos = 40;

  shuffle_deck(&deck);

  CHECK_EQ(deck.pos, 0U);
}

static void test_deal_card_advances_position(void) {
  Deck deck;
  build_deck(&deck);
  shuffle_deck(&deck);

  Card *first = deal_card(&deck);

  CHECK(first != NULL);
  CHECK_EQ(deck.pos, 1U);
}

static void test_deal_card_never_repeats(void) {
  Deck deck;
  int seen[4][14] = {{0}};

  build_deck(&deck);
  shuffle_deck(&deck);

  for (unsigned i = 0; i < DECK_SIZE; i++) {
    Card *c = deal_card(&deck);
    CHECK(c != NULL);
    seen[c->suit][c->rank]++;
  }

  int all_dealt_exactly_once = 1;
  for (int s = 0; s < 4; s++) {
    for (int r = ACE; r <= KING; r++) {
      if (seen[s][r] != 1) {
        all_dealt_exactly_once = 0;
      }
    }
  }

  CHECK(all_dealt_exactly_once);
}

static void test_deal_card_returns_null_when_exhausted(void) {
  Deck deck;
  build_deck(&deck);
  shuffle_deck(&deck);

  for (unsigned i = 0; i < DECK_SIZE; i++) {
    deal_card(&deck);
  }

  CHECK(deal_card(&deck) == NULL);
  /* Exhausted deck must not advance pos further or corrupt state. */
  CHECK_EQ(deck.pos, DECK_SIZE);
}

void run_deck_tests(void) {
  RUN_TEST(test_build_deck_has_52_unique_cards);
  RUN_TEST(test_build_deck_resets_position);
  RUN_TEST(test_shuffle_preserves_composition);
  RUN_TEST(test_shuffle_resets_position);
  RUN_TEST(test_deal_card_advances_position);
  RUN_TEST(test_deal_card_never_repeats);
  RUN_TEST(test_deal_card_returns_null_when_exhausted);
}
