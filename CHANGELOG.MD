# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

### Added

- Added a hidden card for the dealer's first card, making the gameplay follow the standard Blackjack rules.
- Added a 1.5x payout for a player Blackjack.

### Changed

- The dealer's first card is now hidden while the player is making decisions.
- The hidden card is revealed when the round ends.
- Prevented a new round from starting when the bet exceeds the player's available money.
- Player Blackjack is now distinguished from a regular win.
- A player and dealer Blackjack now results in a push.

## [0.1.1]

### Added
 - A separate file, `input.c`, into which the functions `handle_betting_input`, `handle_player_input`, and `handle_round_over_input` were moved from `main.c` and `game.c`
 - Added centered modal notifications to display the result of each round (win, lose, push, blackjack, etc.). Notifications remain on screen until dismissed, making important game events easier to notice.

### Changed
 - `finish_round` is no longer a static function
 - The game now waits for player confirmation before starting the next betting phase.
 - Simplified the round transition flow after displaying the round result.

 ### Fixed
- Fixed a bug where increasing or decreasing the bet could move it one step beyond the configured betting limits. The bet is now properly clamped between `MIN_BET` and `MAX_BET`, ensuring only valid wager amounts can be selected.

## [0.1.0]

### Added
- Basic ncurses initialization (`initscr`, `cbreak`, `noecho`, `keypad`)
- Card, Deck, and Hand modules separating game data from game logic
- Deck build/shuffle/deal using a Fisher-Yates shuffle
- `GameState` struct consolidating deck, dealer hand, player hand, money, and bet into a single explicit object passed by pointer throughout the codebase
- `GamePhase` field (`STATE_BETTING`, `STATE_PLAYING`, `STATE_ROUND_OVER`) added to `GameState`, replacing ad-hoc input handling in `main()`
- `handle_betting_input()` and `handle_round_over_input()` in `main.c`, and `handle_player_input()` in `game.c`, as phase-specific input handlers
- Blackjack hand scoring with soft-ace adjustment (Aces count as 11, drop to 1 as needed to avoid busting)
- Win/lose/push determination (`determine_winner`) and payout application (`apply_result`)
- ncurses UI split into header (balance/bet), card rendering, and playground composition
- First working card rendering via `newwin` and `box`
- Card subwindow lifecycle management (`HandRenderer`) to prevent leaking `WINDOW*` subwindows on every redraw
- Bet increase/decrease controls (`KEY_UP` / `KEY_DOWN`) with min/max clamping
- `.gitignore` for build artifacts, editor files, and OS-generated files

### Fixed
- `newwin()` argument order bug (height/width were swapped with y/x position), which prevented the card window from appearing
- Implicit `stdscr` refresh on `getch()` overwriting the drawn card window; resolved by refreshing `stdscr` before creating overlapping subwindows and standardizing on `wnoutrefresh()` + `doupdate()` instead of ad-hoc `refresh()`/`wrefresh()` calls
- `player_turn()` bust check evaluating the previous hand's state instead of the newly dealt card's state
- Missing bounds checks on deck position and hand size that could silently corrupt data or fail without feedback
- `draw_bet()` incorrectly using `sizeof(int)` instead of the actual formatted string length for centering
- Card subwindows never being freed (`delwin`) before being recreated on each redraw, leaking memory over time
- `Deck` module improperly depending on `Hand`, inverting the intended dependency direction; resolved by splitting `draw_card` (deck-only) from `deal_to_hand` (hand-level combinator)

### Changed
- Replaced global `extern` game-state variables (`dealer_hand`, `player_score`, etc.) with a single `GameState` struct passed explicitly to functions
- Reorganized source into responsibility-based modules (`card`, `deck`, `hand`, `game`, `input`, `ui_header`, `ui_cards`, `ui_playground`) instead of a flat `logic.c` / `ui.c` split
- Removed the blocking `player_turn()` input loop in favor of single-keypress-driven `handle_player_input()`, called from `main()`'s phase dispatch loop
- Split `start_round()` into `begin_round()` (deal initial cards, transition to `STATE_PLAYING`) and `finish_round()` (resolve outcome, transition to `STATE_ROUND_OVER`)
- Replaced `main()`'s flat `switch(ch)` with `switch(game.phase)`, dispatching each keypress to a phase-specific handler
