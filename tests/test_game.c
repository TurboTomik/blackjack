#include "game.h"
#include "test.h"

#include <string.h>

static GameState game;

static void setup(void) {
  memset(&game, 0, sizeof(GameState));
  init_game_state(&game, 1000, 10);
}

static void test_trigger_and_dismiss_notification(void) {
  setup();
  game.phase = STATE_BETTING;

  trigger_notification(&game, NOTIF_INSUFFICIENT_FUNDS);

  CHECK_EQ(game.phase, STATE_BETTING);
  CHECK_EQ(game.previous_phase, STATE_BETTING);
  CHECK_EQ(game.active_notification, NOTIF_INSUFFICIENT_FUNDS);

  dismiss_notification(&game);

  CHECK_EQ(game.phase, STATE_BETTING);
  CHECK_EQ(game.active_notification, NOTIF_NONE);
}

void run_game_tests(void) { RUN_TEST(test_trigger_and_dismiss_notification); }
