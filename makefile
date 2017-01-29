CC = gcc
FILES = main.c functions.c gameFunctions.c listFunctions.c
CC_FLAGS = -Wall -Wextra -g

all:
	$(CC) $(FILES) $(CC_FLAGS) -o explodingDjanni
