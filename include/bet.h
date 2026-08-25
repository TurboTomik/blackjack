#ifndef BET_H
#define BET_H

#define MIN_BET 50
#define MAX_BET (MIN_BET * 5)
#define STEP_BET 5

void bet_increase(unsigned *bet);
void bet_decrease(unsigned *bet);

#endif // !BET_H
