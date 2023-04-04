/**
* File: main.c
* 
* Author: Anjola Aina
* Last Modified: Thursday, March 30th, 2023
*
* Driver file for testing purposes.
*/
#include "main.h"

bool game_over = false;

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


    for (int i = 0; i < ; i++) {
        move_snake(snake, game_board);
        bool lost_game = out_of_bounds(game_board);
        if (lost_game) {
            printf("Uh oh! The snake has touched the end of the board!\n");
            break;
        }
        print_board(game_board);
    }

    /* while (!game_over) {
        move_snake(snake, game_board);
        if (!out_of_bounds(game_board)) {
            print_board(game_board);
        } else {
            game_over = true;
        }
    } // while  */
    

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

void handle_snake_out_of_bounds(queue* snake, board* game_board, direction dir) {
    int snake_row = snake->front->cell.row; // 6
    int snake_col = snake->front->cell.col; // -1
    printf("Snake row: %d\n", snake_row);
    printf("Snake col: %d\n", snake_col);
    if ((snake_row < 0 && snake_row > BOARD_SIZE - 1) || (snake_col < 0 && snake_col > BOARD_SIZE - 1)) {
        printf("OK!\n\n");
        switch (dir) {
            case left:
                change_cell_in_board(game_board, create_cell(snake_row, snake_col, EMPTY));
                print_board(game_board);
                printf("\n\n");
                break;
            case right:
                change_cell_in_board(game_board, create_cell(snake_row, --snake_col, EMPTY));
                print_board(game_board);
                printf("\n\n");
                break;
            case up:
                change_cell_in_board(game_board, create_cell(snake_row, snake_col, EMPTY));
                break;
            case down:
                change_cell_in_board(game_board, create_cell(snake_row, snake_col, EMPTY));
                break;
        } // switch
    } // if
} // handle_snake_out_of_bounds

/**
Checks whether the snake is out of bounds.
This function can be made multithreaded.
*/
bool out_of_bounds(board* game_board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) { 
            if (game_board->cells[i][j]->type == SNAKE) {
                return false;
            } // if
        } // inner for
    } // outer for
    return true;
} // out_of_bounds

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
    fflush(stdin);
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
            printf("X pos: %d, Y pos: %d\n", snake->front->cell.row, snake->front->cell.col);
            update_board(snake, game_board, left);
            handle_snake_out_of_bounds(snake, game_board, left);
            break;
        case 'R':
            move_right(snake, right); 
            //printf("X pos: %d, Y pos: %d\n", snake->front->cell.row, snake->front->cell.col);
            update_board(snake, game_board, right);  
            handle_snake_out_of_bounds(snake, game_board, right);          
            break;
        case 'U':
            move_up(snake, up);
            //printf("X pos: %d, Y pos: %d\n", snake->front->cell.row, snake->front->cell.col);
            update_board(snake, game_board, up);
            handle_snake_out_of_bounds(snake, game_board, up);          
            break;
        case 'D':
            move_down(snake, down);
            //printf("X pos: %d, Y pos: %d\n", snake->front->cell.row, snake->front->cell.col);
            update_board(snake, game_board, down);
            handle_snake_out_of_bounds(snake, game_board, down);          
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