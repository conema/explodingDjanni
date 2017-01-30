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
void menu(Player players[NPLAYERS], Deck*);
void newGame(Player players[NPLAYERS], Deck*);
void loadMode(Player palyers[NPLAYERS], const int, Deck*);
void startGame(Player players[NPLAYERS], Deck *deckCards, int nRound);

#endif // FUNCTIONS_H_