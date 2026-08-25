#ifndef CARD_H
#define CARD_H

typedef enum {
  ACE = 1,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
} Rank;

enum { MAX_CARD_VALUE = 10, ACE_VALUE = 11, ACE_ADJUSTMENT = 10 };

typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } Suit;

typedef struct {
  Rank rank;
  Suit suit;
} Card;

int card_value(Rank rank);

#endif // !CARD_H
