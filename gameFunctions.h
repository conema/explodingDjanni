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
void printAlive(const Player players[NPLAYERS], const int currentPlayer);
Card removeCardPlayer(Player* player, const int pos);
void addCardPlayer(Player* player, Card card);
void chooseCard(Deck *deckCards, Player players[NPLAYERS], const int currentPlayer, int *special);
Deck* drawCard(Player* player, Deck* deckCards);
Deck* isExplosive(Player* player, Deck* deckCards);
void cardEffect(Deck *deckCards, Player players[NPLAYERS], const Card card, const int currentPlayer, int *special);
_Bool callNope(Player players[NPLAYERS], const int currentPlayer, const Card card);
void specialDjanni(Player player[NPLAYERS], const int currentPlayer , const int nDjanni);

#endif // GAME_FUNCTIONS_H_