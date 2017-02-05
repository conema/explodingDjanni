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
Note dall'autore:
  Mi stavo annoiando, quindi mi sono permesso una leggera vena artistica, spero sia cosa grata :D
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
               deckCards = loadMode(players, deckCards, nRound, sc);
               currentPlayer = (rand() % NPLAYERS);
               break;
        case 2:
               deckCards = loadGame(players, deckCards, &attackNext, &currentPlayer);
               break;
        case 3:
               //credits();
               break;
    }

    startGame(players, deckCards, nRound, currentPlayer, attackNext);

  return 0;
}