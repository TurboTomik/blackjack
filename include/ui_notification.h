#ifndef UI_NOTIFICATION_H
#define UI_NOTIFICATION_H

#include <ncurses.h>

typedef enum {
  NOTIF_NONE = 0,
  NOTIF_INSUFFICIENT_FUNDS,
  NOTIF_RESULT_PLAYER_WIN,
  NOTIF_RESULT_DEALER_WIN,
  NOTIF_RESULT_PUSH,
  NOTIF_RESULT_BUST
} NotificationType;

void render_notification(WINDOW *win, NotificationType notification);

#endif // !UI_NOTIFICATION_H
