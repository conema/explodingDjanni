#ifndef LIST_FUNCTIONS_H_
#define LIST_FUNCTIONS_H_

#include "commons.h"
#include "types.h"
#include "gameFunctions.h"

Deck* insertHead(Deck *first, Card card);
int ListDimension(Deck *first);
void printList(Deck *first);
Deck* deleteHead(Deck *first);

#endif // LIST_FUNCTIONS_H_