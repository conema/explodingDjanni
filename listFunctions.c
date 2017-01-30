#include "listFunctions.h"

//Inserimento nuovo nodo in testa
Deck* insertHead(Deck *first, Card card){
  Deck *nuovoNodo = (Deck*) malloc(sizeof(Deck));
  nuovoNodo->card = card;
  nuovoNodo->next = first;
 
  return nuovoNodo;
}

//Inserimento in posizione
Deck* moveCard(Deck *first, const int from, const int to){

}

//Dimensione totale lista
int listDimension(Deck *first){
	if(first == NULL){
    	return 0;
  	}
 
  	return listDimension(first->next) + 1;
}

void printList(Deck *first){
  if(first == NULL){
    return;
  }
 
  printCard(first->card);
  printList(first->next);
}

Deck* deleteHead(Deck *first){
  if(first != NULL){
    Deck *tempNodo = first;
    first = first->next;
    free(tempNodo);
  }
  return first;
}