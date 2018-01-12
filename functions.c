#include "functions.h"


/* Gestione degli argomenti */
void inlineHelper(const int argc, char** argv){
    if(argc >= 2){
        if(!strcmp("-help", argv[1])){
            printf("Questi sono i comandi che puoi fare:\n -help: per vedere i comandi disponibili\n");
        }else{
            printf("Il comando non è stato riconosciuto. Scrivi -help per vedere i comandi\n");
            exit(-1);
        }
    }
}

/* Introduzione al gioco */
void intro(){
    printf(
"             _.-^^---....,,--\n"
"         _ --                 --_\n"
"        (<       " COLOR_RED_BLINK " Exploding  "COLOR_RESET"   >)\n"
"         |       " COLOR_RED_BLINK " Djanni     "COLOR_RESET"   |\n"
"         \\._                  _./\n"
"                  | |   |\n"
"      |\\___/|     |   | |\n"
"      )     (  .-=| | | |=-.\n"
"     =\\     /= `-=#$%%&%%#=-'\n"
"       )===(      |;  : |\n"
"     /       \\    |;  : |\n"
"     \\       /    |;  : |\n"
"\\_/\\_/\\__  _/_/\\_/\\_/\\_/|_\n"
"|  |  |( (  |  |  |  |  |\n"
"|  |  | ) ) |  |  |  |  |\n"
"Benvenuto, buona partita ad Exploding Djanni\n");
}

/* Pulizia console */
void clearConsole(){
    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef linux
        system("clear");
    #endif
    #ifdef __APPLE__
        system("clear");
    #endif
}

/* Controllo input numerico */
void checkNumber(int *n){
    //Controllo input numerico
    if(!scanf("%i", n)){
        printf("E' stato inserito un carattere non valido.\n");
        exit(-1);
    }
}

/* Scrittura riga a log */
void newLogPlayer(Player player1, Player player2, Card card, const int nRound, Log log){
    char type[][16] = {"EXPLODINGDJANNI", "MEOOOW", "SHUFFLE", "NOPE", "SEETHEFUTURE", "ATTACK", "SKIP", "FAVOR", "DJANNICARD"};
    FILE *fp = fopen (LOGNAME, "a+");
    int i;

    fprintf(fp, "Turno %i: ", nRound);
    if(log == DRAW){
        if(card.cardType == DJANNICARD){
            fprintf(fp, "%s ha pescato %s\n", player1.name, card.description);
        }else{
            fprintf(fp, "%s ha pescato %s\n", player1.name, type[card.cardType]);
        }
    }else if(log == DEATH){
        fprintf(fp, "%s e' esploso\n", player1.name);
    }else if(log == CHOOSE){
        if(card.cardType == DJANNICARD){
            fprintf(fp, "%s ha giocato %s\n", player1.name, card.description);
        }else{
            fprintf(fp, "%s ha giocato %s\n", player1.name, type[card.cardType]);
        }
    }else if(log == NOP){
        fprintf(fp, "%s ha annullato la carta\n", player1.name);
    }else if(log == FAV){
        if(card.cardType == DJANNICARD){
            fprintf(fp, "%s ha dato una carta %s a %s\n", player2.name, card.description, player1.name);
        }else{
            fprintf(fp, "%s ha dato una carta %s a %s\n", player2.name, type[card.cardType], player1.name);
        }
    }else if(log == DJSTOLE){
        if(card.cardType == DJANNICARD){
            fprintf(fp, "%s ha rubato la carta %s a %s\n", player1.name, card.description, player2.name);
        }else{
            fprintf(fp, "%s ha rubato la carta %s a %s\n", player1.name, type[card.cardType], player2.name);
        }
    }else if(log == MEOW){
        fprintf(fp, "%s si e' salvato con una meow\n", player1.name);
    }else if(log == START){
        if(player1.alive == false){
            fprintf(fp, "Il giocatore %s è morto", player1.name);
        }else{
            fprintf(fp, "%s ha le seguenti carte: ", player1.name);

            for(i = 0; i < player1.nCards; i++){
                if(player1.cards[i].cardType == DJANNICARD){
                   fprintf(fp, "%s/", player1.cards[i].description);
                }else{
                    fprintf(fp, "%s/", type[player1.cards[i].cardType]);
                }
            }
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}

/* Menù iniziale */
int menu(){
    int sc = 0;
    do{
        printf(
            "(1) New game\n"
            "(2) Load game\n"
            "Qual'e' la tua scelta?\n"
        );

        checkNumber(&sc);
    }while(!(sc >= FIRSTCHOICEMENU && sc <= LASTCHOICEMENU));

    return sc;
}

/* Inizio nuova partita */
void newGame(Player players[NPLAYERS]){
    int sc = 0;
    int i;
    char scc;

    do{
        printf(
            "Stai iniziando una nuova partita. Che difficolta' vuoi?\n"
            "(1) Schiappa\n"
            "(2) Allenamento\n"
            "(3) TrucidaMici\n"
            );
        checkNumber(&sc);
    }while(!(sc >= FIRSTCHOICE && sc <= LASTCHOICE));

    printf("Perfetto, hai scelto la modalita' N. %i, preparatevi alla battaglia!\n", sc);
    printf("Inserisci il nome dei tuoi avversari:\n");

    for(i = 0; i < NPLAYERS; i++){
        #if (DEBUG != 1)
        getchar();
        printf("Giocatore %i:\n Nome: ", i+1);
        scanf("%23[^\n]s", players[i].name);
        getchar();
        do{
            printf("Il giocatore e' un NPC? (y o n)\n");
            scanf("%c", &scc);
        }while(!(scc == 'y' || scc == 'n'));

        if(scc == 'y'){
            players[i].playerType = NPC;
        }else{
            players[i].playerType = HUMAN;
        }

        #endif

        #if (DEBUG == 1)
        players[i].playerType = HUMAN;
        #endif

        players[i].alive = true;
        players[i].nCards = 0;
    }
}

/* Caricamento partita */
Deck* loadGame(Player players[NPLAYERS], Deck *deckCards, _Bool *attackNext, int *currentPlayer){
    char dir[STRLEN] = DIRSAVES;
    char fileName[NAMELEN];
    int i = 0, j;
    int nCardDeck;
    Card tempCard;

    printf("Insersci il nome del tuo salvataggio:\n");

    #ifdef _WIN32
        system("dir saves");
    #endif
    #ifdef linux
        system("ls " DIRSAVES);
    #endif
    #ifdef __APPLE__
        system("ls " DIRSAVES);
    #endif

    getchar();
    scanf("%23[^\n]s", fileName);

    strcat(dir, fileName);

    FILE * fp = fopen(dir, "rb");

    if(fp == NULL){
        printf("File non esistente.\n");
        exit(-1);
    }

    //Lettura dati giocatori
    for(i = 0; i < NPLAYERS; i++){
        fread(players[i].name, sizeof(char), NAMELEN, fp);
        fread(&players[i].alive, sizeof(_Bool), 1, fp);

        if(players[i].alive){
            fread(&players[i].nCards, sizeof(int), 1, fp);
            fread(&players[i].playerType, sizeof(PlayerType), 1, fp);

            players[i].cards = (Card*)malloc(sizeof(Card) * players[i].nCards); //Allocamento memoria carte
            for(j = 0; j < players[i].nCards; j++){
                fread(&players[i].cards[j].description, sizeof(char), STRLEN, fp);
                fread(&players[i].cards[j].cardType, sizeof(CardType), 1, fp);
            }
        }
    }

    fread(&nCardDeck, sizeof(int), 1, fp);

    for(i = 0; i < nCardDeck; i++){
        fread(&tempCard.description, sizeof(char), STRLEN, fp);
        fread(&tempCard.cardType, sizeof(CardType), 1, fp);
        deckCards = insertHead(deckCards, tempCard);
    }

    fread(currentPlayer, sizeof(int), 1, fp);
    fread(attackNext, sizeof(_Bool), 1, fp);

    fclose(fp);

    return deckCards;
}

/* Salvataggio partita */
void saveGame(Player players[NPLAYERS], Deck *deckCards, int currentPlayer, _Bool attackNext){
    char dir[STRLEN] = DIRSAVES;
    char fileName[NAMELEN];
    int nCardDeck = listDimension(deckCards);
    int i = 0, j;
    Deck *tempDeck = deckCards;

    printf("Insersci il nome del tuo salvataggio:\n Salvataggi presenti:\n");

    #ifdef _WIN32
        system("dir saves");
    #endif
    #ifdef linux
        system("ls " DIRSAVES);
    #endif
    #ifdef __APPLE__
        system("ls " DIRSAVES);
    #endif

    getchar();
    scanf("%23[^\n]s", fileName);

    strcat(dir, fileName);

    FILE * fp = fopen(dir, "wb");

    if(fp == NULL){
        exit(-1);
    }

    //Scrittura dati giocatori
    for(i = 0; i < NPLAYERS; i++){
        fwrite(players[i].name, sizeof(char), NAMELEN, fp);
        fwrite(&players[i].alive, sizeof(_Bool), 1, fp);

        if(players[i].alive){
            fwrite(&players[i].nCards, sizeof(int), 1, fp);
            fwrite(&players[i].playerType, sizeof(PlayerType), 1, fp);

            for(j = 0; j < players[i].nCards; j++){
                fwrite(&players[i].cards[j].description, sizeof(char), STRLEN, fp);
                fwrite(&players[i].cards[j].cardType, sizeof(CardType), 1, fp);
            }
        }
    }

    fwrite(&nCardDeck, sizeof(int), 1, fp);

    for(i = 0; i < nCardDeck; i++){
        fwrite(tempDeck->card.description, sizeof(char), STRLEN, fp);
        fwrite(&tempDeck->card.cardType, sizeof(CardType), 1, fp);
        tempDeck = tempDeck->next;
    }

    fwrite(&currentPlayer, sizeof(int), 1, fp);
    fwrite(&attackNext, sizeof(_Bool), 1, fp);

    fclose(fp);
}

/* Caricamento modalità da file */
Deck* loadMode(Player players[NPLAYERS], Deck *deckCards, const int mode){
    FILE *fp = NULL;
    int totCards = 0, countExplosiveCards = 0, countMeowCards = 0, i;
    int nExplosive, nMeow, nDjanni, cardType;
    char description[STRLEN];
    Card *explosiveCards, *meowCards;
    Card newCard;

    switch(mode){
        case 1:
               fp = fopen(DIRMODES "explodingDjanniEasy.txt", "r");
               break;
        case 2:
               fp = fopen(DIRMODES "explodingDjanniMedium.txt", "r");
               break;
        case 3:
               fp = fopen(DIRMODES "explodingDjanniHard.txt", "r");
               break;
    }

    if(fp == NULL){
        printf("Errore nell'apertura dei file modalita', file di gioco corrotti.\n");
        exit(-1);
    }

    //Lettura su file della quantità delle carte
    fscanf(fp, "%i %i %i\n", &nExplosive, &nMeow, &nDjanni);

    explosiveCards = (Card*)malloc(sizeof(Card)*nExplosive);
    meowCards = (Card*)malloc(sizeof(Card)*nMeow);

    if(explosiveCards == NULL|| meowCards == NULL){
        printf("Problemi con la memoria.\n");
        exit(-1);
    }

    //Caricamento carte in memoria da file
    while(!feof(fp) && totCards < (nDjanni+nExplosive+nMeow)){
        fscanf(fp, "%i %[^\n]s\n", &cardType, description);
        if(cardType == EXPLODINGDJANNI){
            //Carte explosive
            if(countExplosiveCards < nExplosive){
                explosiveCards[countExplosiveCards].cardType = cardType;
                strcpy(explosiveCards[countExplosiveCards].description, description);
                countExplosiveCards++;
            }
        }else if(cardType == MEOOOW){
            //Carte meow
            if(countMeowCards < nMeow){
                meowCards[countMeowCards].cardType = cardType;
                strcpy(meowCards[countMeowCards].description, description);
                countMeowCards++;
            }
        }else{
            //Inserimento delle altre carte
            newCard.cardType = cardType;
            strcpy(newCard.description, description);

            deckCards = insertHead(deckCards, newCard);
        }

        totCards++;
    }
    fclose(fp);

    //Il Deck viene mischiato
    shuffleDeck(deckCards);

    //Le carte vengono consegnate
    deckCards = giveCards(players, deckCards, meowCards, &nMeow);

    //Aggiunta carte meow al mazzo
    for(i = nMeow; i > 0; i--){
        deckCards = insertHead(deckCards, meowCards[i]);
    }
    //Aggiunta carte explosive al mazzo
    for(i = 0; i < nExplosive; i++){
        deckCards = insertHead(deckCards, explosiveCards[i]);
    }

    //Cancellazione memoria occupata dalla lista carte meow ed explosive
    free(meowCards);
    free(explosiveCards);

    //Il deck viene mischiato con le nuove carte
    shuffleDeck(deckCards);


    #if (DEBUG == 1)
        //printf("\n\nstart %i\n\n", (nDjanni+nMeow+nExplosive));
        //printList(deckCards);
    #endif

    return deckCards;
}

/* Inizio partita */
Deck* startGame(Player players[NPLAYERS], Deck *deckCards, int nRound, int currentPlayer, _Bool attackNext){
    int sc, scCard, playersAlive, special = 0;
    _Bool playing = true;
    int i;

    //Inserimento carte utenti nel log
    for(i = 0; i < NPLAYERS; i++){
        newLogPlayer(players[i], players[i], deckCards->card, nRound, START);
    }

    getchar();
    printf(COLOR_WHITE_BLINK "\nCaricamento file di gioco completato, premi invio per iniziare a giocare." COLOR_RESET);
    getchar();


    while(playing){
        if(currentPlayer >= NPLAYERS){
            //Reset turno giocatore
            currentPlayer = 0;
        }

        playersAlive = countAlive(players);

        if(players[currentPlayer].alive == true && players[currentPlayer].playerType == HUMAN && playersAlive > 1){
            //Turno player
            do{
                clearConsole();

                printf("\nTurno: %i, tocca a %s\nLe tue carte:\n", nRound,players[currentPlayer].name);
                printDeck(players[currentPlayer].cards, players[currentPlayer].nCards);

                if(attackNext){
                    printf(COLOR_RED "\nAttenzione, sei sotto attacco.\n" COLOR_RESET);
                }

		        printf("\n(0) Gioca carta\n(1) Pesca carta\n(2) Salva la partita\n(3) Esci dalla partita\n");
		        checkNumber(&sc);

                if(sc == 0){
                    if(players[currentPlayer].nCards != 0){
		                do{
			                printf("Inserisci il numero della carta che vuoi giocare: (-1 per tornare indietro)\n");
			                checkNumber(&scCard);
		                }while(scCard < -1 || scCard >= players[currentPlayer].nCards);

                        if(scCard != -1){
                            chooseCard(deckCards, players, currentPlayer, &special, nRound, scCard);
                        }
                    }else{
		                printf("Non hai più carte in mano.\n");
	                }
	            }else if(sc == 2){
                    saveGame(players, deckCards, currentPlayer, attackNext);
			        printf("Partita salvata\n");
		        }else if(sc == 3){
                    return deckCards;
                }

                getchar();
                printf("\nPremi invio per continuare.\n");
                getchar();
	        }while(sc != 1 && special == 0);
        }else if(players[currentPlayer].alive == true && players[currentPlayer].playerType == NPC && playersAlive > 1){
            //Turno NPC
            while(chooseCardBot(players, deckCards, currentPlayer, &special, nRound, attackNext) && special == 0);
            sc = 1;
        }

        //Controllo fine partita e stampa vincitore
        if(players[currentPlayer].alive == true && playersAlive == 1){
            clearConsole();
            playing = false;
            printf("\n\nComplimenti %s, hai vinto la partita!\n\n", players[currentPlayer].name);

            FILE *fp = fopen (LOGNAME, "a+");
            fprintf(fp, "Turno %i: %s ha vinto\n", nRound, players[currentPlayer].name);
            fclose(fp);
        }

        if(players[currentPlayer].alive == true && playersAlive > 1){
            if(sc == 1 && special != SKIP && special != ATTACK){
                deckCards = drawCard(&players[currentPlayer], deckCards, nRound);
            }

            if(special == ATTACK && attackNext == false){
                //Attacco prossimo giocatore
                attackNext = true;
            }else if(special != ATTACK && attackNext == true){
                //Giocatore attaccato: ri-gioca il turno
                currentPlayer--;
                attackNext = false;
            }

            special = 0;
            nRound++;
        }

        currentPlayer++;
    }

    return deckCards;
}
