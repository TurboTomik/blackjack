#ifndef UI_CARD_H
#define UI_CARD_H

#include "hand.h"
#include "ncurses.h"

#define CARD_HEIGH 7
#define CARD_WIDTH 9
#define CARD_PADDING 1

typedef struct {
  WINDOW *windows[MAX_HAND_SIZE];
  unsigned count;
} HandRenderer;

void draw_hand_cards(HandRenderer *renderer, WINDOW *orig, const Hand *hand,
                     int line, int hide_first);

#endif // !UI_CARD_H
