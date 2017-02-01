#include "gameFunctions.h"

//Funzione mischia carte
void shuffleDeck(Deck *deckCards){
	int i, nRand, size;
	Card temp;
	Deck *current = deckCards;

	size = listDimension(deckCards);

	Card* deckTemp = NULL;
	deckTemp = (Card*)malloc(size*sizeof(Card));
	if(deckTemp == NULL){
        printf("Problemi con la memoria.\n");
        exit(-1);
    }

	//La lista viene copiata in un vettore
	for(i = 0; i < size; i++){
		deckTemp[i] = current->card;
		current = current->next;
	}

	//Il vettore viene mischiato
	for (i = 0; i < size; i++){
    	nRand = rand() % size;
      	temp = deckTemp[nRand];
		deckTemp[nRand] = deckTemp[i];
      	deckTemp[i] = temp;
    }

	current = deckCards;

	//Il vettore mischiato viene copiato nella lista
	for(i = 0; i < size; i++){
		current->card = deckTemp[i];
		current = current->next;
	}

	free(deckTemp);
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
Card removeCardPlayer(Player* player, const int pos){
	Card tempCard;
	int nCards = --(*player).nCards;

	//La carta da eliminare è spostata alla fine del mazzo
	tempCard = (*player).cards[nCards];
	(*player).cards[nCards] = (*player).cards[pos];
	(*player).cards[pos] = tempCard;

	//Re-allocazione della memoria
	(*player).cards = (Card*)realloc((*player).cards, nCards * sizeof(Card));

	return tempCard;
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
void chooseCard(Deck *deckCards, Player players[NPLAYERS], const int currentPlayer, int *special){
	int sc;
	int nCards = players[currentPlayer].nCards;

	if(nCards != 0){
		do{
			printf("Inserisci il numero della carta che vuoi giocare:\n");
			checkNumber(&sc);
		}while(sc < 0 || sc >= nCards);

		cardEffect(deckCards, players, players[currentPlayer].cards[sc], currentPlayer, special);
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
		do{
			printf("\nAttenzione! Potresti morire, vuoi usare la tua carta meooow? (y o n)\n");
			scanf("%c", &sc);
		}while(sc != 'y' && sc != 'n');
		getchar();
		if(sc == 'y'){
			//Spostamento casuale carta explosion
			nRand = rand()%(listDimension(deckCards));
			deckCards = moveCard(deckCards, 0, nRand);

			//Rimozione carta meow del giocatore
			removeCardPlayer(player, meowPos);
		}else{
			printf("Hai deciso di morire... Sadico...\nPremi invio per continuare\n");
			getchar();
			(*player).alive = false;
			free((*player).cards);
			deckCards = deleteHead(deckCards);
		}
	}else{
		printf("Sei morto!\nPremi invio per continuare\n");
		getchar();
		(*player).alive = false;
		free((*player).cards);
		deckCards = deleteHead(deckCards);
	}

	return deckCards;
}

//Controllo dell'effetto speciale della carta
void cardEffect(Deck *deckCards, Player players[NPLAYERS], const Card card, const int currentPlayer, int *special){
	_Bool noped = false;
	if(card.cardType != MEOOOW && card.cardType != EXPLODINGDJANNI){
		//Viene richiesto agli altri giocatori se  voglio invocare la loro nope
		noped = callNope(players, currentPlayer, card);

		if(!noped){
			if(card.cardType == SHUFFLE){
				printf("Il mazzo viene mischiato.\n");
				shuffleDeck(deckCards);
			}else if(card.cardType == SEETHEFUTURE){

			}else if(card.cardType == ATTACK){
				printf("Il giocatore attacca il prossimo giocatore. \n");
				*special = ATTACK;
			}else if(card.cardType == SKIP){
				printf("Il giocatore salta il turno. \n");
				*special = SKIP;
			}else if(card.cardType == FAVOR){

			}
		}else{
			printf("La tua carta è stata annullata da una carta NOPE!\n");
		}
	}
}

//Controlla la presenza di NOPE e ne consente l'utilizzo
_Bool callNope(Player players[NPLAYERS], const int currentPlayer, const Card card){
	int i, j;
	char sc;
	for(i = 0; i < NPLAYERS; i++){
		if(players[i].alive && i != currentPlayer){
			for(j = 0; j < players[i].nCards; j++){
				if(players[i].cards[j].cardType == NOPE){			
					do{
						clearConsole();
						getchar();
            			printf("\n%s, vuoi usare la tua carta NOPE per annullare la carta ", players[i].name);
						printType(card);
						printf("? (y o n)\n");
            			scanf("%c", &sc);
        			}while(!(sc == 'y' || sc == 'n'));

        			if(sc == 'y'){
						removeCardPlayer(&players[i], j);
						return true;
        			}
				}
			}
		}
	}

	return false;
}