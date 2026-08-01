#include "hand.h"
#include "deck.h"
#include "stdlib.h"

int deal_to_hand(Deck *deck, Hand *hand) {
  if (hand->count >= MAX_HAND_SIZE)
    return 0;

  Card *c = deal_card(deck);
  if (c == NULL)
    return 0;

  hand->cards[hand->count++] = *c;
  return 1;
}

int calculate_hand_score(Hand *hand) {
  int total = 0, aces = 0;

  for (int i = 0; i < hand->count; i++) {
    total += card_value(hand->cards[i].rank);
    if (hand->cards[i].rank == ACE)
      aces++;
  }
  while (total > BLACKJACK && aces > 0) {
    total -= 10;
    aces--;
  }
  hand->score = total;
  return total;
}

int is_bust(const Hand *hand) { return hand->score > BLACKJACK; }
