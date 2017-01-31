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
		players[i].cards = (Card*)malloc(0);	//Alloco memoria 0, poi verrà riallocata in seguito per ogni carta
		if(players[i].cards == NULL){
        	printf("Problemi con la memoria.\n");
        	exit(-1);
		}

		for(j = 0; j < CARDSFORPLAYER; j++){
			//La carta viene assegnata al giocatore e cancellata dal mazzo
			addCardPlayer(&players[i], temp->card);
			temp = deleteHead(temp);
		}
		//Assegnamento carta meow
		addCardPlayer(&players[i], meowCards[i]);
		*nMeow = *nMeow-1;
	}

	return temp;
}

//Stampa la carta
void printCard(Card card){
	printType(card);
	printf(" \n    %s\n", card.description);
}

//Stampa tipo carta
void printType(Card card){
	char type[][16] = {"EXPLODINGDJANNI", "MEOOOW", "SHUFFLE", "NOPE", "SEETHEFUTURE", "ATTACK", "SKIP", "FAVOR", "DJANNICARD"};
	printf("%s", type[card.cardType]);
}

//Conta giocatori vuoti
int countAlive(const Player players[NPLAYERS]){
	int i, cont = 0;
	for(i = 0; i < NPLAYERS; i++){
		if(players[i].alive == true){
			cont++;
		}
	}
	return cont;
}

//Elimina la carta del giocatore
void removeCardPlayer(Player* player, const int pos){
	Card tempCard;
	int nCards = --(*player).nCards;

	//La carta da eliminare è spostata alla fine del mazzo
	tempCard = (*player).cards[nCards];
	(*player).cards[nCards] = (*player).cards[pos];
	(*player).cards[pos] = tempCard;

	//Re-allocazione della memoria
	(*player).cards = (Card*)realloc((*player).cards, nCards * sizeof(Card));
}

//Aggiungere carta al mazzo del giocatore
void addCardPlayer(Player* player, Card card){
	int nCards = ++(*player).nCards;

	//Re-allocazione della memoria
	(*player).cards = (Card*)realloc((*player).cards, nCards * sizeof(Card));

	//La carta viene aggiunta
	(*player).cards[nCards-1] = card;
}

//Gioca una carta
void chooseCard(Player players[NPLAYERS], const int currentPlayer){
	int sc;
	int nCards = players[currentPlayer].nCards;

	if(nCards != 0){
		do{
			printf("Inserisci il numero della carta che vuoi giocare:\n");
			checkNumber(&sc);
		}while(sc < 0 || sc >= nCards);

		removeCardPlayer(&players[currentPlayer], sc);

	}else{
		printf("Non hai più carte in mano.\n");
	}

}

//Pesca una carta
Deck* drawCard(Player* player, Deck* deckCards){
	if(deckCards == NULL){
		printf("Il mazzo è vuoto\n");
	}else{
		if(deckCards->card.cardType == EXPLODINGDJANNI){
		    deckCards = isExplosive(player, deckCards);
		}else{
			//Viene aggiunta la carta pescata
			addCardPlayer(player, deckCards->card);
			deckCards = deleteHead(deckCards);
		}
	}

	return deckCards;
}

Deck* isExplosive(Player* player, Deck* deckCards){
	_Bool meow = false;
	int i, meowPos, nRand;
	char sc;
	for(i = 0; i < (*player).nCards; i++){
		if((*player).cards[i].cardType == MEOOOW){
			meow = true;
			meowPos = i;
			break;
		}
	}

    printf(
     "      /\\_/\\\n"
     " /\\  / o o \\\n"
     "//\\\\ \\~(*)~/\n"
     " , \\/   ^ /\n"
     "   | \\|| || \n"
     "   \\ '()=()            ________\n"
     "    \\)__H_,,__        (__((___()\n"    
     "      |ACME |\\\\______(__((___()()\n"								                     
     "      |_____| '-----(__((___()()()\n");

	if(meow == true){
		getchar();
		do{
			printf("\nAttenzione! Potresti morire, vuoi usare la tua carta meooow? (y o n)\n");
			scanf("%c", &sc);
		}while(sc != 'y' && sc != 'n');

		if(sc == 'y'){
			//Spostamento casuale carta explosion
			nRand = rand()%(listDimension(deckCards)-1);
			deckCards = moveCard(deckCards, 0, nRand);

			//Rimozione carta meow del giocatore
			removeCardPlayer(player, meowPos);
		}else{
			printf("Hai deciso di morire... Sadico...");
			(*player).alive = false;
			free((*player).cards);
			deckCards = deleteHead(deckCards);
		}
	}else{
		printf("Sei morto!");
		(*player).alive = false;
		free((*player).cards);
		deckCards = deleteHead(deckCards);
	}

	return deckCards;
}