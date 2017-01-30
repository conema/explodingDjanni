#ifndef LIST_FUNCTIONS_H_
#define LIST_FUNCTIONS_H_

#include "commons.h"
#include "types.h"
#include "gameFunctions.h"

Deck* insertHead(Deck *first, Card card);
Deck* moveCard(Deck *first, const int from, const int to);
int listDimension(Deck *first);
void printList(Deck *first);
Deck* deleteHead(Deck *first);

#endif // LIST_FUNCTIONS_H_