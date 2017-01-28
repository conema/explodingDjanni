#include "commons.h"
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
void menu(){
    int sc = 0;
    do{
        printf(
            "(1) New game\n"
            "(2) Load game\n"
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
               newGame();
               break;
        case 2:
               loadGame();
               break;
    }
}