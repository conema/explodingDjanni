#ifndef TYPES_H_
#define TYPES_H_

#include "commons.h"
typedef enum {EXPLODINGDJANNI, MEOOOW, SHUFFLE, NOPE, SEETHEFUTURE, ATTACK, SKIP, FAVOR, DJANNICARD} CardType;
typedef enum {HUMAN, NPC} PlayerType;
typedef enum {CHOOSE, DRAW, NOP, DEATH, FAV, DJSTOLE, MEOW, START} Log;

typedef struct{
	CardType cardType;
	char description[STRLEN];
}Card;

typedef struct{
	char name[NAMELEN];
	_Bool alive;
	int nCards;
	PlayerType playerType;
	Card* cards;
}Player;

typedef struct deck{
	Card card;
	struct deck *next;
}Deck;

#endif // TYPES_H_