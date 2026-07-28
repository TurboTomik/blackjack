#include "deck.h"
#include "card.h"
#include <stdlib.h>

void
build_deck (Deck *deck)
{
  int i = 0;
  for (Suit s = HEARTS; s <= SPADES; s++)
    for (Rank r = ACE; r <= KING; r++)
      {
        deck->cards[i].rank = r;
        deck->cards[i].suit = s;
        i++;
      }
}

void
shuffle_deck (Deck *deck)
{
  for (int i = DECK_SIZE - 1; i > 0; i--)
    {
      int j = rand () % (i + 1);
      Card tmp = deck->cards[i];
      deck->cards[i] = deck->cards[j];
      deck->cards[j] = tmp;
    }
  deck->pos = 0;
}

Card *
deal_card (Deck *deck)
{
  if (deck->pos >= DECK_SIZE)
    return NULL;
  return &deck->cards[deck->pos++];
}
