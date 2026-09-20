#include "layout.h"
#include <ncurses.h>

#define HEADER_HEIGHT 1
#define BOTTOM_HEIGHT 1
#define POPUP_HEIGHT 6
#define POPUP_WIDTH 50

void init_layout(GameLayout *layout) {
  if (!layout) {
    return;
  }

  free_layout(layout);

  int playground_height = LINES - HEADER_HEIGHT - BOTTOM_HEIGHT;

  int popup_y = (LINES - POPUP_HEIGHT) / 2;
  int popup_x = (COLS - POPUP_WIDTH) / 2;

  if (popup_y < 0) {
    popup_y = 0;
  }
  if (popup_x < 0) {
    popup_x = 0;
  }

  layout->header = newwin(HEADER_HEIGHT, COLS, 0, 0);
  layout->playground = newwin(playground_height, COLS, HEADER_HEIGHT, 0);
  layout->bottom = newwin(BOTTOM_HEIGHT, COLS, LINES - BOTTOM_HEIGHT, 0);
  layout->popup = newwin(POPUP_HEIGHT, POPUP_WIDTH, popup_y, popup_x);
}

void free_layout(GameLayout *layout) {
  if (!layout) {
    return;
  }

  if (layout->header) {
    delwin(layout->header);
    layout->header = NULL;
  }
  if (layout->playground) {
    delwin(layout->playground);
    layout->playground = NULL;
  }
  if (layout->bottom) {
    delwin(layout->bottom);
    layout->bottom = NULL;
  }
  if (layout->popup) {
    delwin(layout->popup);
    layout->popup = NULL;
  }
}
