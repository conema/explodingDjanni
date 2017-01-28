#ifndef TYPES_H_
#define TYPES_H_

#include "commons.h"
typedef enum {NOPE, ATTACK, SKIP, FAVOR, SEETHEFUTURE, SHUFFLE, DJANNICARD, EXPLODINGDJANNI, MEOOOW} CardType;
typedef enum {HUMAN, NPC} PlayerType;

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

#endif // TYPES_H_