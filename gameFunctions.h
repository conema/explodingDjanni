#ifndef GAME_FUNCTIONS_H_
#define GAME_FUNCTIONS_H_

#include "commons.h"
#include "types.h"

void shuffleDeck(Card *deckCards, const int size);
void printDeck(Card *deckCards, const int size);
void giveCards(Player* players, Card *deckCards/*, Card * explosiveCards, Card * meowCards, const int djanni, const int explosive, const int meow*/);

#endif // GAME_FUNCTIONS_H_