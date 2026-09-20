#include "test.h"

#include <string.h>

#include "round.h"

static GameState game;

static void setup(void) {
  memset(&game, 0, sizeof(GameState));
  init_game_state(&game, 1000, 10);
}

static void test_can_double_down(void) {
  setup();
  begin_round(&game);

  CHECK(can_double_down(game.money, game.bet, game.player.count));

  CHECK(!can_double_down(game.money, game.bet, 3));

  CHECK(!can_double_down(15, 10, 2));
}

static void test_begin_round_success(void) {
  setup();

  begin_round(&game);

  CHECK_EQ(game.phase, STATE_PLAYER_TURN);
  CHECK_EQ(game.player.count, 2);
  CHECK_EQ(game.dealer.count, 2);
  CHECK_NE(game.player.score, 0);
  CHECK_NE(game.dealer.score, 0);
}

static void test_begin_round_insufficient_funds(void) {
  setup();
  game.money = 5;
  game.bet = 10;

  begin_round(&game);

  CHECK_EQ(game.phase, STATE_NOTIFICATION);
  CHECK_EQ(game.active_notification, NOTIF_INSUFFICIENT_FUNDS);
}

static void test_player_hit(void) {
  setup();
  begin_round(&game);

  if (game.phase == STATE_PLAYER_TURN) {
    uint8_t initial_count = game.player.count;

    player_hit(&game);

    if (game.phase == STATE_PLAYER_TURN) {
      CHECK_EQ(game.player.count, (unsigned int)initial_count + 1);
    } else {
      CHECK_EQ(game.phase, STATE_NOTIFICATION);
      CHECK(is_bust(&game.player));
    }
  }
}

static void test_player_stand(void) {
  setup();
  begin_round(&game);

  player_stand(&game);

  CHECK(game.dealer.score >= DEALER_STAND || is_bust(&game.dealer));
  CHECK_EQ(game.phase, STATE_NOTIFICATION);
}

static void test_player_double_down(void) {
  setup();
  begin_round(&game);
  unsigned int initial_bet = game.bet;

  player_double_down(&game);

  CHECK_EQ(game.bet, initial_bet * 2);
  CHECK_EQ(game.phase, STATE_NOTIFICATION);
}

static void test_trigger_and_dismiss_notification(void) {
  setup();
  game.phase = STATE_BETTING;

  trigger_notification(&game, NOTIF_INSUFFICIENT_FUNDS);

  CHECK_EQ(game.phase, STATE_NOTIFICATION);
  CHECK_EQ(game.previous_phase, STATE_BETTING);
  CHECK_EQ(game.active_notification, NOTIF_INSUFFICIENT_FUNDS);

  dismiss_notification(&game);

  CHECK_EQ(game.phase, STATE_BETTING);
  CHECK_EQ(game.active_notification, NOTIF_NONE);
}

void run_round_tests(void) {
  RUN_TEST(test_can_double_down);

  RUN_TEST(test_begin_round_success);
  RUN_TEST(test_begin_round_insufficient_funds);

  RUN_TEST(test_player_hit);
  RUN_TEST(test_player_stand);
  RUN_TEST(test_player_double_down);

  RUN_TEST(test_trigger_and_dismiss_notification);
}
