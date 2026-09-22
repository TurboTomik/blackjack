#include "bet.h"
#include "game.h"
#include "input.h"
#include "layout.h"
#include "round.h"
#include "ui.h"
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void initialization() {
  setlocale(LC_ALL, "");
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

int main(void) {
  GameState game;
  int ch;
  char running = 1;

  initialization();
  srand(time(NULL));
  init_game_state(&game, INIT_MONEY, MIN_BET);
  init_layout(&game.layout);

  while (running) {
    render_game(&game);

    ch = getch();

    if (ch == 'q') {
      running = 0;
      continue;
    }

    if (ch == KEY_RESIZE) {
      handle_resize(&game);
      continue;
    }

    switch (game.phase) {
    case STATE_BETTING:
      handle_betting_input(&game, ch);
      break;
    case STATE_PLAYER_TURN:
      handle_player_input(&game, ch);
      break;
    case STATE_NOTIFICATION:
      handle_result_input(&game, ch);
      break;
    case STATE_DEALER_TURN:
    case STATE_FINISHED:
      break;
    }
  }

  free_layout(&game.layout);
  endwin();
  return 0;
}
