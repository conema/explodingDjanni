#ifndef COMMONS_H_
#define COMMONS_H_

/*		INCLUDE		*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/*		DEFINE     */
#define DEBUG 1
#define NPLAYERS 4
#define CARDSFORPLAYER 4

//Grandezza stringhe
#define STRLEN 128
#define NAMELEN 24

//Quantità scelte
#define FIRSTCHOICE 1
#define LASTCHOICE 3

//Directory contenente i txt delle modalita'
#define DIRMODES "modes/"

//Directory contenete i salvataggi
#define DIRSAVES "saves/"

//http://www.linuxjournal.com/article/8603
#define COLOR_RED     "\x1b[31m"
#define COLOR_RED_BLINK "\033[5;31;3m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[36m"
#define COLOR_WHITE_BLINK "\033[5;37;3m"
#define COLOR_BROWN    "\033[01;30m"
#define COLOR_RESET   "\x1b[0m"


#endif // COMMONS_H_