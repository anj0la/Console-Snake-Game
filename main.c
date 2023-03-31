/**
* File: main.c
* 
* Author: Anjola Aina
* Last Modified: Thursday, March 30th, 2023
*
* Driver file for testing purposes.
*/
#include "main.h"

void print_cells(node* front) {
    if (front == NULL) {
        return;
    }
    else {
        printf("Row: %d, Col: %d, Cell Type: %s\n", front->cell.row, front->cell.col, cell_type_names[front->cell.type]);
        print_cells(front->next);
    }
}



int main(void) {
    srand(time(NULL));
    printf("Welcome to Snake!\n");
    board* game_board = create_board();
    queue* snake = create_queue();
    change_cell_in_board(game_board, create_cell(BOARD_SIZE / 2, BOARD_SIZE / 2, SNAKE)); // starts in middle of the board
    enqueue(snake, create_cell(BOARD_SIZE / 2, BOARD_SIZE / 2, SNAKE)); // starts in middle of the board
    printf("Printing the board... \n");
    print_board(game_board);
    /* print_cells(snake->front);
    dequeue(snake);
    printf("Queue after Dequeue \n");
    print_cells(snake->front);  */
    free_queue(snake); 
    free_board(game_board);
    return 0;
}