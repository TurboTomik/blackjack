#ifndef UI_PLAYGROUND_H
#define UI_PLAYGROUND_H

#include "game.h"
#include "result.h"
#include <ncurses.h>

#define PLAYGROUND_BEGIN_LINE 1
#define PLAYGROUND_MARGIN_BOT 4

#define DEALER_LABEL "Dealer"
#define DEALER_LABEL_LINE 2
#define DEALER_SCORE_LINE (DEALER_LABEL_LINE + CARD_HEIGH + 1)

#define PLAYER_LABEL "Player"
#define PLAYER_LABEL_LINE (DEALER_SCORE_LINE + 4)
#define PLAYER_SCORE_LINE (PLAYER_LABEL_LINE + CARD_HEIGH + 1)

void render_playground(const GameState *game, int hide_dealer_hole);
void display_result(GameResult result);

#endif // !UI_PLAYGROUND_H
