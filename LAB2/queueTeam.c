#include<stdio.h>
#include<stdlib.h>
#include <string.h>

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
  // Numero de elementos do time
  int numberOfElements;

  // Array de elementos do time
  int* elements;
} Team;

typedef struct {
  // id
  int scenario;

  // Array de times de um cenario
  Team* teams;
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
void  enqueue(Queue *queue, int newElement) {
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
}

// Funcao que remove um item do queue
// Altera a head
void dequeue(Queue *queue) {
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
    printf("%d\n", head);
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


void commandsLoop(Queue *queue) {
    char command[256];
    do {
        scanf("%s", command);
        //printf("%s\n", command);
        if (strcmp(command, "ENQUEUE") == 0) {
           int element;
            scanf("%d", &element);
            enqueue(queue, element);
        }
        else if (strcmp(command, "DEQUEUE") == 0) {
            dequeue(queue);
        }
    } while (strcmp(command, "STOP") != 0);
}

// Percorre o elemento dos times e vai preenchenco o queue
void elementsLoop(Queue *queue, int numberOfTeams) {
    int numberOfElements, element;
    int size = 0;
    Team *team = (Team*) malloc(sizeof(Team));
    
    for (int i=1; i<=numberOfTeams; ++i) {
        // Le o numero de elementos
        scanf("%d", &numberOfElements);
        size += numberOfElements;
        
        team->elements = (int*) malloc(sizeof(int) * numberOfElements);

        for (int j=0; j<numberOfElements; ++j) {
            scanf("%d\n", &element);
            team->elements[j] = element;
        }
    }
}

int main (int argc, char *argv[]) {
    int scenario;
    int numberOfTeams;
    Queue *queue;

    // Loop principal
    scenario = 1;
    do {
        // Inicializando a queue
        queue = initializeQueue(100);

        // Le o numero de times
        scanf("%d\n", &numberOfTeams);
        if (numberOfTeams == 0) exit(0);

        // Printa o scenario
        printf("Scenario #%d\n", scenario);

        // Inicia o ciclo
        elementsLoop(queue, numberOfTeams);
        commandsLoop(queue);
        free(queue);
        scenario++;
        //printf("\n");
    } while (numberOfTeams != 0);

    return 0;
}
