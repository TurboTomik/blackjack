#include "ui_header.h"
#include <ncurses.h>

static const char msg_balance[] = "Balance: ";
static const char msg_bet[] = "Bet: ";

static void draw_balance(unsigned money) {
  mvprintw(0, 0, "%s%d$", msg_balance, money);
}

static void draw_bet(unsigned bet) {
  enum { HEADER_BUFFER_SIZE = 32 };

  char buf[HEADER_BUFFER_SIZE];
  int len = snprintf(buf, sizeof(buf), "%s%d$", msg_bet, bet);
  int x = getmaxx(stdscr);
  int center_posx = (x - len) / 2;

  mvprintw(0, center_posx, "%s", buf);
}

void render_header(WINDOW *win, unsigned money, unsigned bet) {
  werase(win);

  draw_balance(money);
  draw_bet(bet);

  wnoutrefresh(win);
}
