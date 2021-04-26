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

Node *findNode(Node *head, int value) {
  Node *temp = head;

  while (temp != NULL) {
    if (temp->value == value) return temp;
    temp = temp->next;
  }

  return NULL;
}

void *insertAfterNode(Node *nodeToInsertAfter, Node* newNode) {
  newNode->next = nodeToInsertAfter->next;
  nodeToInsertAfter->next = newNode;
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

void enqueue(Queue *queue, Team *data[], int numberOfTeams, int value) {
  Node *newNode = createNewNode(value);
  Node *temp = queue->head;
 
  while (temp != NULL) {  
    if (findElementTeam(data, numberOfTeams, temp->value) == findElementTeam(data, numberOfTeams, value)) {
      insertAfterNode(temp, createNewNode(value));
      return;
    }
    temp = temp->next;
  }

  // Adiciona o novo elemento no final do queue
  if (queue->tail != NULL) {
    queue->tail->next = newNode;
  }
  queue->tail = newNode;

  // Se a queue esta vazia, adiciona o novo elemento na head
  if (queue->head == NULL) {
    queue->head = newNode;
  }
}

void dequeue(Queue *queue) {
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

  printf("%d\n", head);
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

void commandsLoop(Queue *queue, Team *data[], int numberOfTeams) {
    char command[256];
    do {
        scanf("%s", command);
        //printf("%s\n", command);
        if (strcmp(command, "ENQUEUE") == 0) {
           int element;
            scanf("%d", &element);
            enqueue(queue, data, numberOfTeams, element);
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
      //printf("%d\n", team->elements[j]);
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
  //free(queue);
  
/*
  Node *head = NULL;
  Node *temp;
  
  for (int i=0; i<25; ++i) {
    temp = createNewNode(i);
    insertInHead(&head, temp);
  }

  temp = findNode(head, 13);
  //printf("\n%d\n", temp->value);

  insertAfterNode(temp, createNewNode(75));

  printLinkedList(head);*/

  //Node *temp;
  //temp = findNode(queue->head, 11);
  //printf("%d\n", temp->value);

  //insertAfterNode(temp, createNewNode(70));

  //printLinkedList(queue->head);

}
