#include "process_manager.h"

void initialize_process_manager(PROCESS_MANAGER *pm) {
    pm->front = 24;
    pm->rear = 25;
    pm->size = 0;
}

bool isFull(PROCESS_MANAGER *pm) {
    return pm->size == MAX_PROCESS;
}

bool isEmpty(PROCESS_MANAGER *pm) {
    return pm->size == 0;
}

void insert_front(PROCESS_MANAGER *pm, PROCESS_QUEUE pq) {
    pm->deque[pm->front] = pq;
    pm->front = (pm->front - 1 + MAX_PROCESS) % MAX_PROCESS;
    pm->size++;
}

void insert_rear(PROCESS_MANAGER *pm, PROCESS_QUEUE pq) {
    pm->deque[pm->rear] = pq;
    pm->rear = (pm->rear + 1) % MAX_PROCESS;
    pm->size++;
}

PROCESS_QUEUE delete_front(PROCESS_MANAGER *pm) {
    pm->size--;
    pm->front = (pm->front + 1) % MAX_PROCESS;
    return pm->deque[pm->front];
}

PROCESS_QUEUE delete_rear(PROCESS_MANAGER *pm) {
    pm->size--;
    pm->rear = (pm->rear - 1 + MAX_PROCESS) % MAX_PROCESS;
    return pm->deque[pm->rear];
}