#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "deck.h"

#define MAX_HAND_SIZE 12
#define BLACKJACK 21

typedef struct
{
  Card cards[MAX_HAND_SIZE];
  unsigned count;
  unsigned score;
} Hand;

int deal_to_hand (Deck *deck, Hand *hand);
int calculate_hand_score (Hand *hand);
int is_bust (const Hand *hand);

#endif // !HAND_H
