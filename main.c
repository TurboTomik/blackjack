#include "game.h"
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
      switch (ch)
        {
        case (KEY_UP):
          bet_increase (&game.bet);
          if (game.bet > MAX_BET)
            game.bet = MAX_BET;
          draw_bet (game.bet);
          wnoutrefresh (stdscr);
          doupdate ();
          break;
        case (KEY_DOWN):
          bet_decrease (&game.bet);
          if (game.bet < MIN_BET)
            game.bet = MIN_BET;
          draw_bet (game.bet);
          wnoutrefresh (stdscr);
          doupdate ();
          break;
        case (' '):
          start_round (&game);
          break;
        case ('q'):
          running = 0;
          break;
        }
    }

  endwin ();
  return 0;
}
