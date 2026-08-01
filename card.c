#include "card.h"

int card_value(Rank rank) {
  if (rank >= TEN)
    return 10;
  if (rank == ACE)
    return 11;
  return rank;
}
