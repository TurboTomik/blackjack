#include "ui_card.h"
#include <ncurses.h>

static const char *
rank_name (Rank rank)
{
  switch (rank)
    {
    case ACE:
      return "A";
    case JACK:
      return "J";
    case QUEEN:
      return "Q";
    case KING:
      return "K";
    default:
      {
        static char buf[3];
        snprintf (buf, sizeof (buf), "%d", rank);
        return buf;
      }
    }
}

static const char *
suit_symbol (Suit suit)
{
  switch (suit)
    {
    case HEARTS:
      return "♥";
    case DIAMONDS:
      return "♦";
    case CLUBS:
      return "♣";
    case SPADES:
      return "♠";
    }
  return "?";
}

static WINDOW *
draw_card (WINDOW *orig, int begin_y, int begin_x, Rank rank, Suit suit)
{
  WINDOW *card = derwin (orig, CARD_HEIGH, CARD_WIDTH, begin_y, begin_x);
  box (card, 0, 0);
  mvwprintw (card, CARD_PADDING, CARD_PADDING, "%s%s", rank_name (rank),
             suit_symbol (suit));
  mvwprintw (card, CARD_HEIGH - 2, CARD_WIDTH - 4, "%2s%s", rank_name (rank),
             suit_symbol (suit));
  wnoutrefresh (card);
  return card;
}

static void
clear_card_windows (HandRenderer *renderer)
{
  for (int i = 0; i < renderer->count; i++)
    {
      delwin (renderer->windows[i]);
      renderer->windows[i] = NULL;
    }
  renderer->count = 0;
}

void
draw_hand_cards (HandRenderer *renderer, WINDOW *orig, const Hand *hand,
                 int line)
{
  clear_card_windows (renderer);

  int row_width = (CARD_WIDTH * hand->count + 2 * (hand->count - 1));
  int row_beginx = getmaxx (orig) / 2 - row_width / 2;

  for (int i = 0; i < hand->count; i++)
    {
      renderer->windows[i]
          = draw_card (orig, line, row_beginx + (i * (CARD_WIDTH + 2)),
                       hand->cards[i].rank, hand->cards[i].suit);
    }
  renderer->count = hand->count;
}
