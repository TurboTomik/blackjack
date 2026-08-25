#include "card.h"

int card_value(Rank rank) {
  if (rank >= TEN) {
    return MAX_CARD_VALUE;
  }
  if (rank == ACE) {
    return ACE_VALUE;
  }
  return rank;
}
