#include<stdio.h>
#include<stdlib.h>

typedef struct {
    // Posicao do primeiro e ultimo elemento
    int head, tail;

    // Tamanho atual
    int size;

    // Capacidade maxima
    int capacity;

    // Array de elementos
    int* elements;
} Queue;

typedef struct {
    int numberOfElements;
    int* elements;
} Team;

typedef struct {
    // Scenario #id
    int scenario;

    // Numeros de times
    int numberOfTeams;

    // Elementos do time
    Team* elements;
} Teams;

int isFull(Queue *queue);
int isEmpty(Queue *queue);
int peek(Queue *queue);

Queue* initializeQueue(int capacity) {
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(0);
    }

    queue->capacity = capacity;
    queue->head = queue->size = 0;

    // Alocando memoria para o array de elementos da queue
    queue->tail = capacity - 1;
    queue->elements = (int*) malloc(sizeof(int) * capacity);

    return queue;
}

// Funcao que adiciona um item a queue
// Altera a tail
int  enqueue(Queue *queue, int newElement) {
    // Verifica se a queue esta cheia
    if (isFull(queue)) {
        // Se sim, produz erro de overflow e encerra o programa
        printf("Nao eh mais possivel adicionar items nessa queue");
        exit(0);
    }
    
    // Se nao estiver cheia, incrementa o ponteiro tail para apontar para o proximo espaco vazio
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->elements[queue->tail] = newElement;
    queue->size = queue->size + 1;
    return newElement;

}

// Funcao que remove um item do queue
// Altera a head
int dequeue(Queue *queue) {
    // Verifica se a queue esta vazia
    if (isEmpty(queue)) {
        // Se sim, produz erro de overflow e encerra o programa
        printf("Nao eh possivel deletar um item de uma queue vazia");
        exit(0);
    }

    // Se nao, acessa o elemento onde a head esta apontando
    int head = peek(queue);
    // Seta uma nova head para o proximo elemento do array
    queue->head = (queue->head + 1);
    queue->size = queue->size - 1;
    return head;
}

// Verifica se a queue esta na sua capacidade maxima
int isFull(Queue *queue) {
    return (queue->size == queue->capacity);
}

// Verifica se a queue esta vazia
int isEmpty(Queue *queue) {
    return (queue->size == 0);
}

// Retorna o elemento na head do queue
int peek(Queue *queue) {
    return queue->elements[queue->head];
}

void commandsLoop() {

}

void elementsLoop(Queue *queue) {
    int numberOfTeams, numberOfElements, element;
    
    // Le o numero de times
    scanf("%d", &numberOfTeams);
    for (int i=0; i<numberOfTeams; ++i) {
        // Le o numero de elementos
        scanf("%d", &numberOfElements);
        for (int j=0; j<numberOfElements; ++j) {
            scanf("%d", &element);
            // Adiciona o elemento na queue
            enqueue(queue, element);
        }
    }

    // Quando termina de ler os numeros, comeca a ler os comandos
    commandsCommands();
}

void teamLoop() {

}

int main (int argc, char *argv[]) {
    int* scenario;
    // Criterio de parada: 0 depois do STOP
}
