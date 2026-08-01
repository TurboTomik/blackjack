#include "ui_header.h"
#include <ncurses.h>

static const char msg_balance[] = "Balance: ";
static const char msg_bet[] = "Bet: ";

void draw_balance(unsigned money) {
  mvprintw(0, 0, "%s%d$    ", msg_balance, money);
}

void draw_bet(unsigned bet) {
  char buf[32];
  int len = snprintf(buf, sizeof(buf), "%s%d$", msg_bet, bet);
  int x = getmaxx(stdscr);
  int center_posx = (x - len) / 2;

  mvprintw(0, center_posx, "%s  ", buf);
}

void draw_header(unsigned money, unsigned bet) {
  draw_balance(money);
  draw_bet(bet);
}
