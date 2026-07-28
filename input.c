#include "input.h"
#include "ui_header.h"
#include "ui_playground.h"
#include <ncurses.h>

void
handle_betting_input (GameState *game, int ch)
{
  switch (ch)
    {
    case KEY_UP:
      bet_increase (&game->bet);
      draw_bet (game->bet);
      wnoutrefresh (stdscr);
      doupdate ();
      break;
    case KEY_DOWN:
      bet_decrease (&game->bet);
      draw_bet (game->bet);
      wnoutrefresh (stdscr);
      doupdate ();
      break;
    case '\n':
    case ' ':
      begin_round (game);
      break;
    }
}

void
handle_player_input (GameState *game, int ch)
{
  switch (ch)
    {
    case ('h'):
      if (!deal_to_hand (&game->deck, &game->player))
        break;
      calculate_hand_score (&game->player);
      draw_playground (game);
      doupdate ();
      if (is_bust (&game->player))
        finish_round (game);
      break;

    case (' '):
      dealer_turn (game);
      finish_round (game);
      break;
    }
}

void
handle_round_over_input (GameState *game, int ch)
{
  (void)ch;
  game->phase = STATE_BETTING;
  draw_header (game->money, game->bet);
  wnoutrefresh (stdscr);
  doupdate ();
}
