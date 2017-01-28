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
  Player players[NPLAYER];
  Card *deckCards = NULL;

  srand(time(NULL));

  inlineHelper(argc, argv);
  intro();
  menu(players, deckCards);
  return 0;
}
