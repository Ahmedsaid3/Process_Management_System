#include "insertion_queue.h"


void initialize_execution_queue(INSERTION_QUEUE *iq) {
    iq->front = 0;
    iq->rear = -1;
    iq->size = 0;
}

bool isFull(INSERTION_QUEUE *iq) {
    return iq->size == MAX_OPERATION;
}

bool isEmpty(INSERTION_QUEUE *iq) {
    return iq->size == 0;
}

PROCESS_QUEUE peek(INSERTION_QUEUE *iq) {
    return iq->queue[iq->front];
}

void enqueue(INSERTION_QUEUE *iq, PROCESS_QUEUE data) {
    iq->queue[++iq->rear] = data;
    iq->size++;
}

PROCESS_QUEUE dequeue(INSERTION_QUEUE *iq) {
    iq->size--;
    return iq->queue[iq->front++];
}