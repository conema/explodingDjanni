#include "listFunctions.h"

//Inserimento nuovo nodo in testa
Deck* insertHead(Deck *first, Card card){
  Deck *nuovoNodo = (Deck*) malloc(sizeof(Deck));
  nuovoNodo->card = card;
  nuovoNodo->next = first;
 
  return nuovoNodo;
}

//Spostamento carta
Deck* moveCard(Deck *first, const int from, const int to){
  Deck *current = first, *next = first->next, *prev = NULL, *fromCard, *toCard;
  int i;

  if(from > (listDimension(first)-1) || to > (listDimension(first)-1) || from == to){
    return first;
  }

  //Scorrimmento lista all'elemento da spostare
  for(i = 0; i < from; i++){
      prev = current;
      current = current->next;
  }

  fromCard = current;

  current = first;
  next = first->next;
   
  if(prev == NULL){
    //Si incrementa la posizione della lista
    first = first->next;
  }else{
    prev->next = fromCard->next;
  }

  //Scorrimento lista alla posizione nella quale l'elemento sarà inserito
  for(i = 0; i < to; i++){
    current = current->next;
    next = next->next;
  }

  toCard = current;

  //La carta viene spostata
  toCard->next = fromCard;
  fromCard->next = next;

  return first;
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