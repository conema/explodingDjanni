#ifndef GAME_FUNCTIONS_H_
#define GAME_FUNCTIONS_H_

#include "commons.h"
#include "types.h"
#include "functions.h"
#include "listFunctions.h"

void shuffleDeck(Deck *deckCards);
void printDeck(Card *deckCards, const int size);
Deck* giveCards(Player* players, Deck *deckCards, Card * meowCards, int *nMeow);
void printCard(Card card);
void printType(Card card);
int countAlive(const Player players[NPLAYERS]);
void removeCardPlayer(Player* player, const int pos);
void addCardPlayer(Player* player, Card card);
void chooseCard(Player players[NPLAYERS], const int currentPlayer);
Deck* drawCard(Player* player, Deck* deckCards);
Deck* isExplosive(Player* player, Deck* deckCards);

#endif // GAME_FUNCTIONS_H_