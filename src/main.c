/**
* File: main.c
* 
* Author: Anjola Aina
* Last Modified: Thursday, March 30th, 2023
*
* Driver file for testing purposes.
*/
#include "main.h"

/**
The entry point of the application.
*/
int main(void) {
    srand(time(NULL));
    printf("Welcome to Snake!\n");

    // Initializing game
    board* game_board = create_board();
    queue* snake = create_queue();
    change_cell_in_board(game_board, create_cell(BOARD_SIZE / 2, BOARD_SIZE / 2, SNAKE)); // starts in middle of the board
    enqueue(snake, create_cell(BOARD_SIZE / 2, BOARD_SIZE / 2, SNAKE)); // starts in middle of the board
    print_board(game_board);

    // Playing the game
    move_snake(snake, game_board);
    print_board(game_board);

    // Freeing all game objects
    free_queue(snake); 
    free_board(game_board);
    return 0;
} // main

/**
Prints all the nodes in the snake.
@param front - the front of the snake
*/
void print_snake_nodes(node* front) {
    if (front == NULL) {
        return;
    }
    else {
        printf("Row: %d, Col: %d, Cell Type: %s\n", front->cell.row, front->cell.col, cell_type_names[front->cell.type]);
        print_snake_nodes(front->next);
    }
} // print_snake_nodes

void update_board(queue* snake, board* game_board, direction dir) {
    node* temp = snake->front;
    while (temp != NULL) {
        int snake_row = temp->cell.row;
        int snake_col = temp->cell.col;
        //printf("In update board, row: %d, col: %d, type: %s\n", snake_row, snake_col, cell_type_names[temp->cell.type]);
        //printf("Board type: %s\n", cell_type_names[game_board->cells[snake_row][snake_col]->type]);
        if (game_board->cells[snake_row][snake_col]->type != SNAKE) {
            change_cell_in_board(game_board, create_cell(snake_row, snake_col, SNAKE));
            switch (dir) {
                case left:
                    change_cell_in_board(game_board, create_cell(snake_row, ++snake_col, EMPTY));
                    break;
                case right:
                    change_cell_in_board(game_board, create_cell(snake_row, --snake_col, EMPTY));
                    break;
                case up:
                    change_cell_in_board(game_board, create_cell(--snake_row, snake_col, EMPTY));
                    break;
                case down:
                    change_cell_in_board(game_board, create_cell(++snake_row, snake_col, EMPTY));
                    break;
            } // switch
        } // if
        temp = temp->next;
    } // while
    free(temp);
} // update_board

/**
Gets input from the user.
@return - the input from the user
*/
char get_input() {
    char user_input;
    printf("It's time to move the snake!\n");
    printf("Press L to move left, R to move right, U to move up, and D to move down.\n");
    fflush(stdout);
    scanf("%c", &user_input);
    return toupper(user_input);
} // get_input


/**
Moves the snake in the specified position determined by user input.
@param snake - the queue representing the snake
*/
void move_snake(queue* snake, board* game_board) {
    char input = get_input();
    switch (input) {
        case 'L':
            move_left(snake, left); // works
            //printf("X pos: %d, Y pos: %d\n", snake->front->cell.row, snake->front->cell.col);
            update_board(snake, game_board, left); // doesn't work
            break;
        case 'R':
            move_right(snake, right); 
            //printf("X pos: %d, Y pos: %d\n", snake->front->cell.row, snake->front->cell.col);
            update_board(snake, game_board, right);            
            break;
        case 'U':
            move_up(snake, up);
            //printf("X pos: %d, Y pos: %d\n", snake->front->cell.row, snake->front->cell.col);
            update_board(snake, game_board, up);
            break;
        case 'D':
            move_down(snake, down);
            //printf("X pos: %d, Y pos: %d\n", snake->front->cell.row, snake->front->cell.col);
            update_board(snake, game_board, down);
            break;
    } // switch
} // move_snake

/**
Moves the snake to the left.
@param snake - the queue representing the snake
*/
void move_left(queue* snake, direction dir) {
    change_cells_in_queue(snake, dir);
} // move_left

/**
Moves the snake to the right.
@param snake - the queue representing the snake
*/
void move_right(queue* snake, direction dir) {
    change_cells_in_queue(snake, dir);
} // move_right

/**
Moves the snake up.
@param snake - the queue representing the snake
*/
void move_up(queue* snake, direction dir) {
    change_cells_in_queue(snake, dir);
} // move_up

/**
Moves the snake down.
@param snake - the queue representing the snake
*/
void move_down(queue* snake, direction dir) {
    change_cells_in_queue(snake, dir);
} // move_down