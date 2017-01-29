#include "functions.h"


//Gestione degli argomenti
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

//Introduzione al gioco
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

//Pulizia console
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

//Menù iniziale
void menu(Player players[NPLAYERS], Deck *deckCards){
    int sc = 0;
    do{
        printf(
            "(1) New game\n"
            "(2) Load game\n"
            "(3) Credits\n"
            "Qual'e' la tua scelta?\n"
        );

        //Controllo input numerico
        if(!scanf("%i", &sc)){
            printf("E' stato inserito un carattere non valido.\n");
            return;
        }
    }while(!(sc >= FIRSTCHOICE && sc <= LASTCHOICE));


    switch(sc){
        case 1:
               newGame(players, deckCards);
               break;
        case 2:
               //loadGame();
               break;
        case 3:
               //credits();
               break;
    }
}

//Inizio nuova partita
void newGame(Player players[NPLAYERS], Deck *deckCards){
    int sc = 0;
    int i;
    char NPC;

    do{
        printf(
            "Stai iniziando una nuova partita. Che difficoltà vuoi?\n"
            "(1) Schiappa\n"
            "(2) Allenamento\n"
            "(3) TrucidaMici\n"
            );

        //Controllo input numerico
        if(!scanf("%i", &sc)){
            printf("E' stato inserito un carattere non valido.\n");
            return;
        }
    }while(!(sc >= FIRSTCHOICE && sc <= LASTCHOICE));

    printf("Perfetto, hai scelto la modalità N°%i, preparatevi alla battaglia!\n", sc);
    printf("Inserisci il nome dei tuoi avversari:\n");

    for(i = 0; i < NPLAYERS; i++){
        #if (DEBUG != 1)
        printf("Giocatore %i:\n Nome: ", i+1);
        scanf("%23s", players[i].name);
        getchar();
        do{
            printf("Il giocatore e' un NPC? (s o n)\n");
            scanf("%c", &NPC);
        }while(!(NPC == 's' || NPC == 'n'));

        if(NPC == 's'){
            players[i].PlayerType = NPC;
        }else{
            players[i].PlayerType = HUMAN;
        }

        #endif
        players[i].alive = true;
        players[i].nCards = 0;
    }

    loadMode(players, sc, deckCards);
}

//Caricamento modalità da file
void loadMode(Player players[NPLAYERS], const int mode, Deck *deckCards){
    FILE *fp = NULL;
    int totCards = 0, countExplosiveCards = 0, countMeowCards = 0, i;
    int nExplosive, nMeow, nDjanni, cardType;
    int nRound = 0;
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
            explosiveCards[countExplosiveCards].cardType = cardType;
            strcpy(explosiveCards[countExplosiveCards].description, description);
            countExplosiveCards++;
        }else if(cardType == MEOOOW){
            //Carte meow 
            meowCards[countMeowCards].cardType = cardType;
            strcpy(meowCards[countMeowCards].description, description);
            countMeowCards++;
        }else{
            //Tutte le altre carte
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

    startGame(players, deckCards, nRound);
}

void startGame(Player players[NPLAYERS], Deck *deckCards, int nRound){
    int currentPlayer;

    //Scelta casuale primo giocatore
    currentPlayer = rand() % NPLAYERS;

    printf(COLOR_WHITE_BLINK "\nCaricamento file di gioco completato, premi invio per iniziare a giocare." COLOR_RESET);
    getchar();
    getchar();
    while(true){
        clearConsole();
        if(currentPlayer >= 4){
            //Reset turno giocatore
            currentPlayer = 0;
        }
        if(players[currentPlayer].alive == true && players[currentPlayer].playerType == HUMAN){
            //Controllo morte giocatore
            printf("\nTocca a %s\nLe tue carte:\n", players[currentPlayer].name);

            printDeck(players[currentPlayer].cards, players[currentPlayer].nCards);

            currentPlayer++;
            nRound++;
        }else if(players[currentPlayer].alive == true && players[currentPlayer].playerType == NPC){

        }
        break;
    }
}