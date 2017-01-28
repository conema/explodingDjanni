#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "commons.h"
#include "types.h"
#include "gameFunctions.h"

_Bool isDigit(int digit);
void inlineHelper(const int, char**);
void intro();
void clearConsole();
void menu(Player players[NPLAYER], Card*);
void newGame(Player players[NPLAYER], Card*);
void loadMode(Player palyers[NPLAYER], const int, Card*);

#endif // FUNCTIONS_H_