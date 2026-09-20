#include "ui_notification.h"
#include <ncurses.h>
#include <string.h>

static const char press_button_msg[] = "(Press any button to continue)";

static const char *notification_to_string(NotificationType type) {
  switch (type) {
  case NOTIF_INSUFFICIENT_FUNDS:
    return "Not enough balance!";
  case NOTIF_RESULT_PLAYER_WIN:
    return "You win!";
  case NOTIF_RESULT_DEALER_WIN:
    return "Dealer wins.";
  case NOTIF_RESULT_PUSH:
    return "Push (Draw).";
  case NOTIF_RESULT_BUST:
    return "Bust! You lose.";
  default:
    return "";
  }
}

void render_notification(WINDOW *win, NotificationType notification) {
  const char *text = notification_to_string(notification);
  if (!win || !text) {
    return;
  }
  werase(win);
  box(win, 0, 0);

  mvwaddstr(win, 2, (getmaxx(win) - strlen(text)) / 2, text);
  mvwaddstr(win, 3, (getmaxx(win) - strlen(press_button_msg)) / 2,
            press_button_msg);

  wnoutrefresh(win);
}
