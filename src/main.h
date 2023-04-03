/**
* File: main.h
* 
* Author: Anjola Aina
* Last Modified: Sunday, April 2nd, 2023
*
* This file controls the execution of the game. Once completed, everything in this file and the main.c file will be transferred over to the 
* game.h and game.c files respectively so that the main file will execute the program.
*/
#ifndef main_h
#define main_h

#include "queue.h"
#include "board.h"
#include <time.h>
#include <ctype.h>

// Function definitions
void print_snake_nodes(node* front);
void update_board(queue* snake, board* game_board, direction dir);
char get_input();
void move_snake(queue* snake, board* game_board);
void move_left(queue* snake, direction dir);
void move_right(queue* snake, direction dir);
void move_up(queue* snake, direction dir);
void move_down(queue* snake, direction dir);

#endif