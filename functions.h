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
void menu(Player players[NPLAYER], Deck*);
void newGame(Player players[NPLAYER], Deck*);
void loadMode(Player palyers[NPLAYER], const int, Deck*);

#endif // FUNCTIONS_H_