#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  // Numero de elementos
  int numberOfElements;

  // Array de elementos
  int* elements;
} Team;

struct Node { // Linked List
  // Elemento armazenado no no
  int value;

  // Ponteiro next
  struct Node* next;
};
typedef struct Node Node;

typedef struct {
  Node *head, *tail;
} Queue;

int findElementTeam(Team *data[], int numberOfTeams, int element);

Node *createNewNode(int value) {
  Node *newNode = (Node*) malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

Node *insertInHead(Node **head, Node *nodeToInsert) {
  nodeToInsert->next = *head;
  *head = nodeToInsert;
  return nodeToInsert;
}

void reverseQueue(Node **head) {
  Node* prev = NULL;
  Node* current = *head;
  Node* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  *head = prev;
}

Node *findNode(Node *head, int value) {
  Node *temp = head;

  while (temp != NULL) {
    if (temp->value == value) return temp;
    temp = temp->next;
  }

  return NULL;
}

void insertAfterNode(Node *nodeToInsertAfter, Node* newNode) {
  // Checa se o no dado eh nulo
  if (nodeToInsertAfter == NULL) exit(0);

  newNode->next = nodeToInsertAfter->next;
  nodeToInsertAfter->next = newNode;
}

void insertBeforeNode(Node *head, Node *nodeToInsertBefore, Node* newNode) {
  Node *prev = head;
  Node *next = head;
  //printf("%d %d\n", prev->value, next->value);
  // Esse loop vai retornar o no anterior ao fornecido

  for (next, prev; next != nodeToInsertBefore; prev = next, next = next->next);
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

Queue *initQueue() {
  Queue *queue = (Queue*) malloc(sizeof(Queue));
  queue->head = queue->tail = NULL;
  return queue;
}

void furaFila(Node *head, Team *data[], int numberOfTeams, int value) {
  if (findElementTeam(data, numberOfTeams, head->value) == findElementTeam(data, numberOfTeams, value)) {
    printf("cheguei aqui");
    insertInHead(&head, createNewNode(value));
    return;
  }
  else {
    Node *temp = head->next;

    while (temp != NULL) {
      printf("Comparando %d com %d\n", temp->value, value);
      if(findElementTeam(data, numberOfTeams, temp->value) == findElementTeam(data, numberOfTeams, value)) {
           printf("Cheguei aqui!\n");
            printf("%d != %d\n", head->value, temp->value);
           insertBeforeNode(head, temp, createNewNode(value));
           return;
      }
      temp = temp->next;
    }
  }
}

void *enqueue(Queue *queue, Team *data[], int numberOfTeams, int value) {
  //furaFila(queue->head, data, numberOfTeams, value);

  if (queue->tail == NULL) {
    queue->head = queue->tail = createNewNode(value);
  } else {
    insertInHead(&queue->head, createNewNode(value));
  }
}

void deleteNode(Queue *queue, Node **head, int value) {
  Node *temp = *head;
  Node *prev = NULL;

  if (temp != NULL && temp->value == value) {
    *head = temp->next;
    free(temp);
    return;
  }

  else {
    while (temp != NULL && temp->value != value) {
      prev = temp; // prev tail
      temp = temp->next; // tail
    }
  }

  if (temp == NULL) return;
  if (prev->next == NULL) {
    prev->next = temp->next;
    queue->tail = prev;
    return;
  }


  prev->next = temp->next;
  free(temp);
}

void dequeue(Queue *queue) {
  if (queue->head == NULL) {
    return;
  }

  if (queue->head == queue->tail) {
    printf("%d\n", queue->head->value);
    queue->head = queue->tail = NULL;
    return;
  }

  Node *temp = queue->head;
  Node *t;
  while (temp->next != NULL) {
    t = temp;
    temp = temp->next;
  }
  printf("%d\n", t->next->value);
  free(t->next);
  t->next = NULL;
  queue->tail = t;
/*
  Node *temp = queue->head;
  queue->head = queue->head->next;
  printf("%d\n", temp->value);
  free(temp);
  // Se a Queue estiver vazia
  if (queue->head == NULL) return;

  // Salvamos a head do queue
  Node *temp = queue->head;
  int head = temp->value;

  // Removemos a head do queue
  queue->head = queue->head->next;
  if (queue->head == NULL) {
    queue->tail = NULL;
  }
  free(temp);

  printf("%d\n", queue->head->value);*/
}

int binarySearch(int elements[], int left, int right, int element) {
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
void *pushNodes(Queue *queue, Team *data[], int numberOfTeams, int value) {
  if (queue->tail == NULL || queue->head == NULL) {
    queue->head = queue->tail = createNewNode(value);
    return;
  }

  // Se o value for do mesmo time do elemento da head
  if (findElementTeam(data, numberOfTeams, queue->head->value) == findElementTeam(data, numberOfTeams, value)) {
    //printf("%d\n", value);
    insertInHead(&queue->head, createNewNode(value));
    return;
  }
  // Caso contrario, procurar o primeiro elemento do time de value
  else {
    Node *temp = queue->head->next;

    while (temp != NULL) {
      if(findElementTeam(data, numberOfTeams, temp->value) == findElementTeam(data, numberOfTeams, value)) {
        insertBeforeNode(queue->head, temp, createNewNode(value));
           return;
      }
      temp = temp->next;
    }
  }

  insertInHead(&queue->head, createNewNode(value));
}

void commandsLoop(Queue *queue, Team *data[], int numberOfTeams) {
    char command[256];
    do {
        scanf("%s", command);
        //printf("%s\n", command);
        if (strcmp(command, "ENQUEUE") == 0) {
           int element;
            scanf("%d", &element);
            pushNodes(queue, data, numberOfTeams, element);
        }
        else if (strcmp(command, "DEQUEUE") == 0) {
            dequeue(queue);
        }
    } while (strcmp(command, "STOP") != 0);
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

  // Armazena o numero total de times
  scanf("%d", &numberOfTeams);

  // Inicializa variavel que vai guardar um array de times
  Team *data[numberOfTeams];
  data[numberOfTeams] = (Team*) malloc(sizeof(Team) * numberOfTeams);

  Queue *queue = initQueue();
  elementsLoop(data, numberOfTeams);
  commandsLoop(queue, data, numberOfTeams);
}
