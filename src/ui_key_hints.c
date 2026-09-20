#include "ui_key_hints.h"
#include "game.h"

#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static const KeyHint bet_key = {"Up/Down", "Bet"};
static const KeyHint deal_key = {"Enter/Space", "Deal"};
static const KeyHint quit_key = {"q", "Quit"};
static const KeyHint hit_key = {"h", "Hit"};
static const KeyHint stand_key = {"Space", "Stand"};
static const KeyHint double_key = {"d", "Double"};

static const char KEY_HINT_FORMAT[] = "[%s] %s";
static const char SEPARATOR[] = " | ";

static int find_start_posx(WINDOW *win, const KeyHint *hints,
                           size_t hint_count) {
  size_t hints_len = 0;
  for (size_t i = 0; i < hint_count; i++) {
    hints_len +=
        snprintf(NULL, 0, KEY_HINT_FORMAT, hints[i].keys, hints[i].action);
    if (i < hint_count - 1) {
      hints_len += strlen(SEPARATOR);
    }
  }
  return ((getmaxx(win) - (int)hints_len) / 2);
}

void render_key_hints(WINDOW *win, GamePhase phase) {
  if (!win) {
    return;
  }

  werase(win);

  const KeyHint *hints = NULL;
  size_t hint_count = 0;

  switch (phase) {
  case STATE_BETTING: {
    static const KeyHint betting_hints[] = {bet_key, deal_key, quit_key};

    hints = betting_hints;
    hint_count = sizeof(betting_hints) / sizeof(betting_hints[0]);
    break;
  }
  case STATE_PLAYER_TURN: {
    static const KeyHint playing_hints[] = {hit_key, stand_key, double_key};

    hints = playing_hints;
    hint_count = sizeof(playing_hints) / sizeof(playing_hints[0]);
    break;
  }
  default:
    break;
  }

  if (hints && hint_count > 0) {
    int start_posx = find_start_posx(win, hints, hint_count);
    if (start_posx < 0) {
      start_posx = 0;
    }

    wmove(win, 0, start_posx);

    for (size_t i = 0; i < hint_count; i++) {
      wprintw(win, KEY_HINT_FORMAT, hints[i].keys, hints[i].action);
      if (i < hint_count - 1) {
        waddstr(win, SEPARATOR);
      }
    }
  }

  wnoutrefresh(win);
}
