#include "card.h"

int card_value(const Rank rank) {
  if (rank >= TEN) {
    return MAX_CARD_VALUE;
  }
  if (rank == ACE) {
    return ACE_VALUE;
  }
  return rank;
}
