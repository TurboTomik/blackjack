#ifndef ROUND_H
#define ROUND_H

#include "game.h"

void init_game_state(GameState *game, unsigned starting_money,
                     unsigned starting_bet);

int can_double_down(unsigned money, unsigned bet, unsigned player_card_count);

void begin_round(GameState *game);

void player_hit(GameState *game);
void player_double_down(GameState *game);
void player_stand(GameState *game);

void trigger_notification(GameState *game, NotificationType type);
void dismiss_notification(GameState *game);

#endif // ROUND_H
