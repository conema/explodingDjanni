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
*/
#include "commons.h"
#include "types.h"
#include "functions.h"

int main(int argc, char *argv[]){
  inlineHelper(argc, argv);
  intro();
  menu();
  return 0;
}
