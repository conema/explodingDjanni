#include "gameFunctions.h"

//Funzione mischia carte
void shuffleDeck(Card *deckCards, const int size){
	int i, nRand;
	Card temp;

    for (i = 0; i < size; i++){
    	nRand = rand() % size;
      	temp = deckCards[nRand];
		deckCards[nRand] = deckCards[i];
      	deckCards[i] = temp;
    }
}

//Stampa le carte
void printDeck(Card *deckCards, const int size){
	int i;
	for(i = 0; i < size; i++){
		printf("Tipo: %i\nDescrizione: %s\n\n", deckCards[i].cardType, deckCards[i].description);
	}
}

//Distribuisce le carte
void giveCards(Player* players, Card *deckCards/*, Card * explosiveCards, Card * meowCards, const int djanni, const int explosive, const int meow*/){
	int i, j;
	int countCards = 0;
	for(i = 0; i < NPLAYER; i++){
		players[i].cards = (Card*)malloc(CARDSFORPLAYER * sizeof(Card));
		if(players[i].cards == NULL){
        	printf("Problemi con la memoria.\n");
        	exit(-1);
		}
		for(j = 0; j < CARDSFORPLAYER; j++){
			players[i].cards[j] = deckCards[countCards];
			//free(&deckCards[countCards]);
			//deckCards = deckCards+countCards;
			countCards++;
		}
	}
}