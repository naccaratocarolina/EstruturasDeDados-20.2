#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int head, tail, size, capacity;
    int* elements;
} Queue;

Queue* initializeQueue(int capacity) {
    Queue *queue = (Queue*) malloc(sizeof(Queue) * capacity);
    if (queue == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(0);
    }

    queue->capacity = capacity;
    queue->head = queue->size = 0;
}

void enqueue() {

}

void dequeue() {

}

struct Queue* peek(Queue *queue) {
    // return queue[head]
}


// Verifica se a queue esta na sua capacidade maxima
int isFull(Queue *queue) {
    return (queue->size == queue->capacity);
}

// Verifica se a queue esta vazia
int isEmpty(Queue *queue) {
    return (queue->size == 0);
}

void show() {

}

int main (int argc, char *argv[]) {
    Queue *queue = initializeQueue(10);

}
