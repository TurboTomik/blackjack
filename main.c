#include "game.h"
#include "input.h"
#include "ui_header.h"
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

GameState *game;

void
initialization ()
{
  setlocale (LC_ALL, "");
  initscr ();
  curs_set (0);
  cbreak ();
  noecho ();
  keypad (stdscr, TRUE);
}

int
main (void)
{
  GameState game;
  int ch;
  char running = 1;

  initialization ();
  srand (time (NULL));

  init_game_state (&game, INIT_MONEY, MIN_BET);
  draw_header (game.money, game.bet);
  wnoutrefresh (stdscr);
  doupdate ();

  while (running)
    {
      ch = getch ();

      if (ch == 'q')
        {
          running = 0;
          continue;
        }

      switch (game.phase)
        {
        case STATE_BETTING:
          handle_betting_input (&game, ch);
          break;
        case STATE_PLAYING:
          handle_player_input (&game, ch);
          break;
        case STATE_ROUND_OVER:
          handle_round_over_input (&game, ch);
        }
    }

  endwin ();
  return 0;
}
