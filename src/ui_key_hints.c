#include "ui_key_hints.h"
#include "game.h"

#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static WINDOW *key_hits_win = NULL;

static const KeyHint bet_key = {"Up/Down", "Bet"};
static const KeyHint deal_key = {"Enter/Space", "Deal"};
static const KeyHint quit_key = {"q", "Quit"};
static const KeyHint hit_key = {"h", "Hit"};
static const KeyHint stand_key = {"Space", "Stand"};
static const KeyHint double_key = {"d", "Double"};

static const char KEY_HINT_FORMAT[] = "[%s] %s";
static const char SEPARATOR[] = " | ";

static int find_start_posx(const KeyHint *hints, size_t hint_count) {
  size_t hints_len = 0;
  for (size_t i = 0; i < hint_count; i++) {
    hints_len +=
        snprintf(NULL, 0, KEY_HINT_FORMAT, hints[i].keys, hints[i].action);
    if (i < hint_count - 1) {
      hints_len += strlen(SEPARATOR);
    }
  }
  return ((getmaxx(key_hits_win) - (int)hints_len) / 2);
}

static void draw_key_hints(const GamePhase phase) {
  const KeyHint *hints;
  size_t hint_count;

  switch (phase) {
  case STATE_BETTING: {
    static const KeyHint betting_hints[] = {bet_key, deal_key, quit_key};

    hints = betting_hints;
    hint_count = sizeof(betting_hints) / sizeof(betting_hints[0]);
    break;
  }
  case STATE_PLAYING: {
    static const KeyHint playing_hints[] = {hit_key, stand_key, double_key};

    hints = playing_hints;
    hint_count = sizeof(playing_hints) / sizeof(playing_hints[0]);
    break;
  }
  default:
    return;
  }

  int start_posx = find_start_posx(hints, hint_count);

  wmove(key_hits_win, 0, start_posx);

  for (size_t i = 0; i < hint_count; i++) {
    wprintw(key_hits_win, KEY_HINT_FORMAT, hints[i].keys, hints[i].action);
    if (i < hint_count - 1) {
      waddstr(key_hits_win, SEPARATOR);
    }
  }
}

static void get_key_hints_win(void) {
  if (!key_hits_win) {
    key_hits_win = newwin(1, COLS, LINES - 1, 0);
  } else {
    werase(key_hits_win);
  }
}

void render_key_hints(GamePhase phase) {
  get_key_hints_win();
  draw_key_hints(phase);

  wnoutrefresh(key_hits_win);
  doupdate();
}
