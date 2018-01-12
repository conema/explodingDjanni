/*
             _.-^^---....,,--
         _ --                 --_
        (<       Exploding      >)
         |         Djanni        |
         \._                  _./
                  | |   |
      |\___/|     |   | |
      )     (  .-=| | | |=-.
     =\     /= `-=#$%&%$#=-'
       )===(      |;  : |
     /       \    |;  : |
     \       /    |;  : |
\_/\_/\__  _/_/\_/\_/\_/|_
|  |  |( (  |  |  |  |  |
|  |  | ) ) |  |  |  |  |

Simulatore del gioco di carte "Exploding Kittens"

PS: Per il corretto funzionamento del programma bisogna settare come "execution working dir" la directory nella quale risiedono i sorgenti del programma.
Questa impostazione si trova nelle impostazioni del progetto (sotto build target) su codeblocks e serve per la corretta lettura dei file di gioco.
*/

#include "commons.h"
#include "types.h"
#include "functions.h"

int main(int argc, char *argv[]){
  Player players[NPLAYERS];
  Deck *deckCards = NULL;
  int sc, currentPlayer;
  _Bool attackNext = false;
  int nRound = 0;

  srand(time(NULL));

  inlineHelper(argc, argv);
  intro();
  sc = menu();

  switch(sc){
        case 1:
               newGame(players);
               deckCards = loadMode(players, deckCards, sc);
               currentPlayer = (rand() % NPLAYERS);
               break;
        case 2:
               deckCards = loadGame(players, deckCards, &attackNext, &currentPlayer);
               break;
    }

    deckCards = startGame(players, deckCards, nRound, currentPlayer, attackNext);

    //Liberazione memoria carte
    freeList(deckCards);
    freeCards(players);
  return 0;
}
