#include "ui_card.h"
#include <ncurses.h>

static const char *rank_name(Rank rank) {
  switch (rank) {
  case ACE:
    return "A";
  case JACK:
    return "J";
  case QUEEN:
    return "Q";
  case KING:
    return "K";
  default: {
    static char buf[3];
    snprintf(buf, sizeof(buf), "%d", rank);
    return buf;
  }
  }
}

static const char *suit_symbol(Suit suit) {
  switch (suit) {
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

static WINDOW *draw_card(WINDOW *orig, int begin_y, int begin_x, Rank rank,
                         Suit suit) {
  WINDOW *card = derwin(orig, CARD_HEIGH, CARD_WIDTH, begin_y, begin_x);
  box(card, 0, 0);
  mvwprintw(card, CARD_PADDING, CARD_PADDING, "%s%s", rank_name(rank),
            suit_symbol(suit));
  mvwprintw(card, CARD_HEIGH - 2, CARD_WIDTH - 4, "%2s%s", rank_name(rank),
            suit_symbol(suit));
  wnoutrefresh(card);
  return card;
}

static WINDOW *draw_card_back(WINDOW *orig, int begin_y, int begin_x) {
  WINDOW *card = derwin(orig, CARD_HEIGH, CARD_WIDTH, begin_y, begin_x);
  box(card, 0, 0);
  for (int y = 1; y < CARD_HEIGH - 1; y++) {
    for (int x = 1; x < CARD_WIDTH - 1; x++) {
      mvwaddch(card, y, x, '?');
    }
  }
  wnoutrefresh(card);
  return card;
}

static void clear_card_windows(HandRenderer *renderer) {
  for (unsigned i = 0; i < renderer->count; i++) {
    delwin(renderer->windows[i]);
    renderer->windows[i] = NULL;
  }
  renderer->count = 0;
}

void draw_hand_cards(HandRenderer *renderer, WINDOW *orig, const Hand *hand,
                     int line, int hide_first) {
  clear_card_windows(renderer);

  int row_width = CARD_WIDTH * (int)hand->count;
  if (hand->count > 1) {
    row_width += 2 * ((int)hand->count - 1);
  }

  int row_beginx = (getmaxx(orig) / 2) - (row_width / 2);

  for (unsigned i = 0; i < hand->count; i++) {
    int x = row_beginx + ((int)i * (CARD_WIDTH + 2));
    if (hide_first && i == 0) {
      renderer->windows[i] = draw_card_back(orig, line, x);
    } else {
      renderer->windows[i] =
          draw_card(orig, line, x, hand->cards[i].rank, hand->cards[i].suit);
    }
  }
  renderer->count = hand->count;
}
