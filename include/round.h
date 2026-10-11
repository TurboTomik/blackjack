#ifndef ROUND_H
#define ROUND_H

#include "game.h"

int can_double_down(unsigned money, unsigned bet, unsigned player_card_count);

void begin_round(GameState *game);

void player_hit(GameState *game);
void player_double_down(GameState *game);
void player_stand(GameState *game);

#endif // ROUND_H
