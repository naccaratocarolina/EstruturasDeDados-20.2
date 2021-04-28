#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados que armazena os times
typedef struct {
  // Numero de elementos
  int numberOfElements;

  // Array de elementos
  int* elements;
} Team;

// Nó da Linked List
struct Node {
  // Elemento armazenado no no
  int value;

  // Ponteiro next
  struct Node* next;
};
typedef struct Node Node;

// Queue
typedef struct {
  Node *head; // ultimo elemento que entrou no queue
  Node *tail; // primeiro elemento que entrou no queue
} Queue;

int findElementTeam(Team *data[], int numberOfTeams, int element);

static Node *createNewNode(int value) {
  Node *newNode = (Node*) malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

static Node *insertInHead(Node **head, Node *nodeToInsert) {
  nodeToInsert->next = *head;
  *head = nodeToInsert;
  return nodeToInsert;
}

void insertAfterNode(Node *nodeToInsertAfter, Node* newNode) {
  if (nodeToInsertAfter == NULL) exit(0);

  newNode->next = nodeToInsertAfter->next;
  nodeToInsertAfter->next = newNode;
}

static void insertBeforeNode(Node *head, Node *nodeToInsertBefore, Node* newNode) {
  Node *prev = head;
  Node *next = head;
  
  // Esse loop vai retornar o no anterior ao fornecido
  for (; next != nodeToInsertBefore; prev = next, next = next->next);

  newNode->next = prev->next;
  prev->next = newNode;
}

void printLinkedList(Node *head) {
  Node *temp = head;

  while (temp != NULL) {
    printf("%d - ", temp->value);
    temp = temp->next;
  }
  printf("\n");
}

static Queue *initQueue() {
  Queue *queue = (Queue*) malloc(sizeof(Queue));
  queue->head = queue->tail = NULL;
  return queue;
}

static int binarySearch(int elements[], int left, int right, int element) {
  if (right >= left) {
    int middle = left + (right - left) / 2;

    if (elements[middle] == element) return middle;
    if (elements[middle] > element) return binarySearch(elements, left, middle - 1, element);
    return binarySearch(elements, middle + 1, right, element);
  }

  return -1;
}

int findElementTeam(Team *data[], int numberOfTeams, int element) {
  // Itera pelos times
  for (int i=0; i<numberOfTeams; ++i) {
    // Itera pelos elementos do time
    for (int j=0; j<data[i]->numberOfElements; ++j) {
      // Se a busca binaria encontrar o elemento, retorna o id do time ao qual ele pertence
      if ((binarySearch(data[i]->elements, 0, data[i]->numberOfElements - 1, element) != -1)) return (i + 1);
    }
  }

  return -1;
}

void *enqueue(Queue *queue, Team *data[], int numberOfTeams, int value) {
  if (queue->tail == NULL || queue->head == NULL) {
    queue->head = queue->tail = createNewNode(value);
    return 0;
  }

  // Se o value for do mesmo time do elemento da head
  if (findElementTeam(data, numberOfTeams, queue->head->value) == findElementTeam(data, numberOfTeams, value)) {
    //printf("%d\n", value);
    insertInHead(&queue->head, createNewNode(value));
    return 0;
  }
  // Caso contrario, procurar o primeiro elemento do time de value
  else {
    Node *temp = queue->head->next;

    while (temp != NULL) {
      if(findElementTeam(data, numberOfTeams, temp->value) == findElementTeam(data, numberOfTeams, value)) {
        insertBeforeNode(queue->head, temp, createNewNode(value));
           return 0;
      }
      temp = temp->next;
    }
  }

  insertInHead(&queue->head, createNewNode(value));
  return 0;
}

void dequeue(Queue *queue) {
  // Se o queue estiver vazio, interrompe o programa
  if (queue->head == NULL) {
    return;
  }

  // Se so tiver 1 elemento no queue, o deleta e corrige a tail
  if (queue->head == queue->tail) {
    printf("%d\n", queue->head->value);
    queue->head = queue->tail = NULL;
    return;
  }

  Node *temp = queue->head;
  Node *prev;
  while (temp->next != NULL) {
    prev = temp; // elemento antes da tail (penultimo)
    temp = temp->next; // tail
  }

  printf("%d\n", prev->next->value);
  free(prev->next);
  prev->next = NULL;
  queue->tail = prev;
}

void commandsLoop(Queue *queue, Team *data[], int numberOfTeams) {
    char command[256];
    do {
      // Le os comandos fornecidos
      scanf("%s", command);

      // Se for ENQUEUE, chama a funcao correspondente com o elemento dado
      if (strcmp(command, "ENQUEUE") == 0) {
        int element;
        scanf("%d", &element);
        enqueue(queue, data, numberOfTeams, element);
      }
      
      // De for DEQUEUE, chama a funcao correspondente
      else if (strcmp(command, "DEQUEUE") == 0) {
        dequeue(queue);
      }
    } while (strcmp(command, "STOP") != 0); // condicao de parada do cenario: STOP
}

void elementsLoop(Team *data[], int numberOfTeams) {
  int numberOfElements, element;

  // Itera pelos times
  for (int i=0; i<numberOfTeams; ++i) {
    // Armazena o numero de elementos do time
    scanf("%d", &numberOfElements);

    // Cria um struct Team
    Team *team = (Team*) malloc(sizeof(Team));

    // Armazena a quantidade de elementos do time
    team->numberOfElements = numberOfElements;

    // Aloca memoria para a quantidade de elementos do time
    team->elements = (int*) malloc(sizeof(int) * numberOfElements);

    for (int j=0; j<numberOfElements; ++j){
      scanf("%d", &element);
      team->elements[j] = element;
    }

    // Preenche o array de times
    data[i] = team;
  }
}

int main (int argc, char *argv[]) {
  int numberOfTeams;
  int scenario;

  // Loop principal
  scenario = 1;
  do {
    // Le o numero de times
    scanf("%d\n", &numberOfTeams);

    // Criterio de parada: numero de times = 0
    if (numberOfTeams == 0) exit(0);

    // Inicializa variavel que vai guardar um array de times
    Team *data[numberOfTeams];
    data[numberOfTeams] = (Team*) malloc(sizeof(Team) * numberOfTeams);

    // Printa o scenario
    printf("Scenario #%d\n", scenario);

    Queue *queue = initQueue();
    elementsLoop(data, numberOfTeams);
    commandsLoop(queue, data, numberOfTeams);

    // Libera o espaco dos ponteiros usados
    free(queue);
    free(data[numberOfTeams]);

    // Incrementa o cenario
    scenario++;
    printf("\n");
  } while (numberOfTeams != 0);

  return 0;
}
