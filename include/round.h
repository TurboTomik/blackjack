#ifndef ROUND_H
#define ROUND_H

#include "game.h"

int can_start_round(unsigned money, unsigned bet);

void init_game_state(GameState *game, unsigned starting_money,
                     unsigned starting_bet);

void start_new_round(GameState *game);

void play_dealer_hand(GameState *game);

int can_double_down(unsigned money, unsigned bet, unsigned player_card_count);

void double_down(GameState *game);

#endif // ROUND_H
