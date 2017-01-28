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
void menu(Player players[NPLAYER], Card *deckCards){
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
void newGame(Player players[NPLAYER], Card *deckCards){
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

    #if (DEBUG != 1)
    for(i = 0; i < NPLAYER; i++){
        printf("Giocatore %i:\n Nome: ", i+1);
        scanf("%23s", players[i].name);
        getchar();
        do{
            printf("Il giocatore e' un NPC? (s o n)\n");
            scanf("%c", &NPC);
        }while(!(NPC == 's' || NPC == 'n'));
        players[i].alive = true;
        players[i].nCards = 0;
    }
    #endif

    loadMode(players, sc, deckCards);
}

//Caricamento modalità da file
void loadMode(Player players[NPLAYER], const int mode, Card *deckCards){
    FILE *fp = NULL;
    int totCards = 0, countDjanniCards = 0, countExplosiveCards = 0, countMeowCards = 0;
    int explosive, meow, djanni, cardType;
    char description[STRLEN];
    Card *explosiveCards, *meowCards;

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
    fscanf(fp, "%i %i %i\n", &explosive, &meow, &djanni);

    deckCards = (Card*)malloc(sizeof(Card)*djanni);
    explosiveCards = (Card*)malloc(sizeof(Card)*explosive);
    meowCards = (Card*)malloc(sizeof(Card)*meow);

    if(deckCards == NULL || explosiveCards == NULL|| meowCards == NULL){
        printf("Problemi con la memoria.\n");
        exit(-1);
    }

    //Caricamento carte in memoria da file
    while(!feof(fp) && totCards < (djanni+explosive+meow)){
        fscanf(fp, "%i %[^\n]s\n", &cardType, description);
        if(cardType == 0){
            explosiveCards[countExplosiveCards].cardType = cardType;
            strcpy(explosiveCards[countExplosiveCards].description, description);
            countExplosiveCards++;
        }else if(cardType == 1){
            meowCards[countMeowCards].cardType = cardType;
            strcpy(meowCards[countMeowCards].description, description);
            countMeowCards++;
        }else{
            deckCards[countDjanniCards].cardType = cardType;
            strcpy(deckCards[countDjanniCards].description, description);
            countDjanniCards++;
        }

        totCards++;
    }
    fclose(fp);

    //Il mazzo viene mischiato
    shuffleDeck(deckCards, djanni);

     #if (DEBUG == 1)
        printDeck(deckCards, djanni);
    #endif

    giveCards(players, deckCards/*, explosiveCards, meowCards, djanni, explosive, meow*/);

    printf("\n\nstart\n\n");
    #if (DEBUG == 1)
        printDeck(players[0].cards, 4);
    #endif
}