/**
* File: queue.h
* 
* Author: Anjola Aina
* Last Modified: Thursday, March 30th, 2023
*
* This file contains the structs and methods associated with initializing a queue,
* adding an element to the queue, and removing an element from the queue. The following website
* was used as a reference to create the queue abstract data type: https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/ 
*/
#ifndef queue_h
#define queue_h
#include "cell.h"

#define EMPTY_QUEUE 0

// The node struct containing data
typedef struct node {
    cell cell;
    struct node *next;
} node;

// The queue struct (the snake will be a queue)
typedef struct queue {
    node* front;
    node* rear;
    int size;
} queue;

// Function definitions
queue* create_queue();
bool is_empty(queue* a_queue);
void enqueue(queue* a_queue, cell* a_cell);
node* dequeue(queue* a_queue);
void free_queue(queue* a_queue);

#endif