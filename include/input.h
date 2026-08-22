#ifndef INPUT_H
#define INPUT_H

#include "game.h"

void handle_betting_input(GameState *game, int ch);
void handle_player_input(GameState *game, int ch);
void handle_round_over_input(GameState *game, int ch);

#endif // !INPUT_H
