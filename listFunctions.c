#include "listFunctions.h"

//Inserimento nuovo nodo in testa
Deck* insertHead(Deck *first, Card card){
  Deck *nuovoNodo = (Deck*) malloc(sizeof(Deck));
  nuovoNodo->card = card;
  nuovoNodo->next = first;
 
  return nuovoNodo;
}

//Dimensione totale lista
int ListDimension(Deck *first){
	if(first == NULL){
    	return 0;
  	}
 
  	return ListDimension(first->next) + 1;
}

void printList(Deck *first){
  if(first == NULL){
    return;
  }
 
  printCard(first->card);
  printList(first->next);
}

Deck* deleteHead(Deck *first){
  if(first->next != NULL){
    Deck *tempNodo = first;
    first = first->next;
    free(tempNodo);
  }
  return first;
}