#ifndef INPUT_H
#define INPUT_H

#include "game.h"

void handle_betting_input(GameState *game, int ch);
void handle_player_input(GameState *game, int ch);
void handle_result_input(GameState *game, int ch);
void handle_resize(GameState *game);

#endif // !INPUT_H
