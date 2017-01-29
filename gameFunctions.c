#include "gameFunctions.h"

//Funzione mischia carte
void shuffleDeck(Deck *deckCards){
	int i, nRand, size;
	Card temp;
	Deck *current = deckCards;

	size = listDimension(deckCards);

	Card* DeckTemp = NULL;
	DeckTemp = (Card*)malloc(size*sizeof(Card));
	if(DeckTemp == NULL){
        printf("Problemi con la memoria.\n");
        exit(-1);
    }

	//La lista viene copiata in un vettore
	for(i = 0; i < size; i++){
		DeckTemp[i] = current->card;
		current = current->next;
	}

	//Il vettore viene mischiato
	for (i = 0; i < size; i++){
    	nRand = rand() % size;
      	temp = DeckTemp[nRand];
		DeckTemp[nRand] = DeckTemp[i];
      	DeckTemp[i] = temp;
    }

	current = deckCards;

	//Il vettore mischiato viene copiato nella lista
	for(i = 0; i < size; i++){
		current->card = DeckTemp[i];
		current = current->next;
	}

	free(DeckTemp);
}


//Stampa le carte
void printDeck(Card *cards, const int size){
	int i;
	for(i = 0; i < size; i++){
		printf("\n    (%i)    ", i);
		printCard(cards[i]);
	}
}

//Distribuisce le carte
Deck* giveCards(Player* players, Deck *deckCards, Card * meowCards, int *nMeow){
	int i, j;
	Deck *temp = deckCards;

	for(i = 0; i < NPLAYERS; i++){
		players[i].cards = (Card*)malloc((CARDSFORPLAYER+1) * sizeof(Card));	//Carte per giocatori + carta meow
		if(players[i].cards == NULL){
        	printf("Problemi con la memoria.\n");
        	exit(-1);
		}

		//La carta viene assegnata al giocatore e cancellata dal mazzo
		for(j = 0; j < CARDSFORPLAYER; j++){
			players[i].cards[j] = temp->card;
			temp = deleteHead(temp);
			players[i].nCards++;
		}
		players[i].cards[CARDSFORPLAYER] = meowCards[i]; 						//Assegnamento carta meow
		*nMeow = *nMeow-1;
		players[i].nCards++;
	}

	return temp;
}

//Stampa la carta
void printCard(Card card){
	printType(card);
	printf(" \n    %s\n", card.description);
}

void printType(Card card){
	char type[][16] = {"EXPLODINGDJANNI", "MEOOOW", "SHUFFLE", "NOPE", "SEETHEFUTURE", "ATTACK", "SKIP", "FAVOR", "DJANNICARD"};
	printf("%s", type[card.cardType]);
}