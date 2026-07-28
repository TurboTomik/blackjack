#ifndef DECK_H
#define DECK_H

#include "card.h"

#define DECK_SIZE 52

typedef struct
{
  Card cards[DECK_SIZE];
  unsigned pos;
} Deck;

void build_deck (Deck *deck);
void shuffle_deck (Deck *deck);
Card *deal_card (Deck *deck);

#endif // DECK_H
