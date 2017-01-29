#ifndef GAME_FUNCTIONS_H_
#define GAME_FUNCTIONS_H_

#include "commons.h"
#include "types.h"
#include "listFunctions.h"

void shuffleDeck(Deck *deckCards);
void printDeck(Card *deckCards, const int size);
Deck* giveCards(Player* players, Deck *deckCards, Card * meowCards, int *nMeow);
void printCard(Card card);

#endif // GAME_FUNCTIONS_H_