#include "bet.h"

void bet_increase(unsigned *bet) {
  if (*bet + STEP_BET > MAX_BET)
    *bet = MAX_BET;
  else
    *bet += STEP_BET;
}

void bet_decrease(unsigned *bet) {
  if (*bet - STEP_BET < MIN_BET)
    *bet = MIN_BET;
  else
    *bet -= STEP_BET;
}
