#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "commons.h"
#include "types.h"
#include "gameFunctions.h"
#include "listFunctions.h"

_Bool isDigit(int digit);
void inlineHelper(const int, char**);
void intro();
void clearConsole();
void checkNumber(int *n);
void newLogPlayer(Player player1, Player player2, Card card, const int nRound, Log log);
int menu();
void newGame(Player players[NPLAYERS]);
Deck* loadGame(Player players[NPLAYERS], Deck* deckCards, _Bool *attackNext, int *currentPlayer);
void saveGame(Player players[NPLAYERS], Deck *deckCards, int currentPlayer, _Bool attackNext);
Deck* loadMode(Player palyers[NPLAYERS], Deck* deckCards, const int mode);
Deck* startGame(Player players[NPLAYERS], Deck *deckCards, int nRound, int currentPlayer, _Bool attackNext);

#endif // FUNCTIONS_H_