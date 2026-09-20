#ifndef UI_HINTS_H
#define UI_HINTS_H

#include "game.h"
#include <ncurses.h>

typedef struct {
  const char *keys;
  const char *action;
} KeyHint;

void render_key_hints(WINDOW *win, GamePhase phase);

#endif // !UI_HINTS_H
