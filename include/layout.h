#ifndef LAYOUT_H
#define LAYOUT_H

#include <ncurses.h>

typedef struct {
  WINDOW *header;
  WINDOW *playground;
  WINDOW *bottom;
  WINDOW *popup;
} GameLayout;

void init_layout(GameLayout *layout);
void free_layout(GameLayout *layout);

#endif // !LAYOUT_H
