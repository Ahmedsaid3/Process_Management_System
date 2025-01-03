#include "process_queue.h"

void initialize_process_queue(PROCESS_QUEUE *pq) {
    pq->front = 0;
    pq->rear = -1;
    pq->size = 0;
    pq->priority = 0; 
    pq->iteration = 0; 
}

bool isFull(PROCESS_QUEUE *pq) {
    return pq->size == QUEUE_SIZE;
}

bool isEmpty(PROCESS_QUEUE *pq) {
    return pq->size == 0;
}

PROCESS peek(PROCESS_QUEUE *pq) {
    return pq->queue[pq->front];
}

void enqueue(PROCESS_QUEUE *pq, PROCESS data) {
    pq->queue[++pq->rear] = data;
    pq->size++;
}

PROCESS dequeue(PROCESS_QUEUE *pq) {
    pq->size--;
    return pq->queue[pq->front++];
}