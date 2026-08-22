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

typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } Suit;

typedef struct {
  Rank rank;
  Suit suit;
} Card;

int card_value(Rank rank);

#endif // !CARD_H
