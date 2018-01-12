#ifndef COMMONS_H_
#define COMMONS_H_

/*		INCLUDE		*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/*		DEFINE     */
#define DEBUG 0
#define NPLAYERS 4
#define CARDSFORPLAYER 4

//Grandezza stringhe
#define STRLEN 128
#define NAMELEN 24

//Quantità scelte
#define FIRSTCHOICEMENU 1
#define LASTCHOICEMENU 2
#define FIRSTCHOICE 1
#define LASTCHOICE 3

//Directory contenente i txt delle modalita'
#define DIRMODES "modes/"

//Directory contenente i salvataggi
#define DIRSAVES "saves/"

//Nome log
#define LOGNAME "log.txt"

//Colori scritte console per essere un po' tamarri
//http://www.linuxjournal.com/article/8603
#define COLOR_RED     "\x1b[31m"
#define COLOR_RED_BLINK "\033[5;31;3m"
#define COLOR_WHITE_BLINK "\033[5;37;3m"
#define COLOR_RESET   "\x1b[0m"

#endif // COMMONS_H_
