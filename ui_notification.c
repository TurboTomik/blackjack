#include "ui_notification.h"
#include <ncurses.h>
#include <string.h>

#define WINDOW_HEIGH 6
#define WINDOW_WIDTH 50

static const char press_button_msg[] = "(Press any button to continue)";

void display_notification(const char *text) {
  WINDOW *window;
  int pos_y, pos_x;
  pos_y = (getmaxy(stdscr) - WINDOW_HEIGH) / 2;
  pos_x = (getmaxx(stdscr) - WINDOW_WIDTH) / 2;

  window = newwin(WINDOW_HEIGH, WINDOW_WIDTH, pos_y, pos_x);
  box(window, 0, 0);

  mvwaddstr(window, 2, (WINDOW_WIDTH - strlen(text)) / 2, text);
  mvwaddstr(window, 3, (WINDOW_WIDTH - strlen(press_button_msg)) / 2,
            press_button_msg);

  wnoutrefresh(window);
  doupdate();
  getch();
  delwin(window);
}
