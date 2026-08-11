#include "game.h"
#include "hand.h"
#include "result.h"
#include "ui_header.h"
#include "ui_playground.h"
#include <ncurses.h>
#include <string.h>

static void reset_hand(Hand *hand) { memset(hand, 0, sizeof *hand); }

void init_game_state(GameState *game, unsigned int starting_money,
                     unsigned int starting_bet) {
  memset(game, 0, sizeof *game);
  game->money = starting_money;
  game->bet = starting_bet;
  game->phase = STATE_BETTING;
}

void begin_round(GameState *game) {
  game->phase = STATE_PLAYING;

  reset_hand(&game->dealer);
  reset_hand(&game->player);

  build_deck(&game->deck);
  shuffle_deck(&game->deck);

  deal_to_hand(&game->deck, &game->dealer);
  deal_to_hand(&game->deck, &game->dealer);
  deal_to_hand(&game->deck, &game->player);
  deal_to_hand(&game->deck, &game->player);

  calculate_hand_score(&game->dealer);
  calculate_hand_score(&game->player);

  draw_playground(game);
  doupdate();
}

void dealer_turn(GameState *game) {
  calculate_hand_score(&game->dealer);
  while (game->dealer.score < DEALER_STAND &&
         deal_to_hand(&game->deck, &game->dealer))
    calculate_hand_score(&game->dealer);

  draw_playground(game);
  doupdate();
}

static void round_over(GameState *game) {
  erase();
  draw_header(game->money, game->bet);
  wnoutrefresh(stdscr);
  doupdate();
}

void finish_round(GameState *game) {
  GameResult result = determine_winner(&game->dealer, &game->player);
  apply_result(&game->money, game->bet, result);

  game->phase = STATE_BETTING;
  draw_playground(game);
  display_result(result);

  round_over(game);
}
