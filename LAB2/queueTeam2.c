#include <stdio.h>
#include <stdlib.h>

typedef struct {
  // Numero de elementos
  int numberOfElements;

  // Array de elementos
  int* elements;
} Team;

int binarySearch(int elements[], int left, int right, int element) {
  if (right >= left) {
    int middle = left + (right - left) / 2;

    if (elements[middle] == element) return middle;
    if (elements[middle] > element) return binarySearch(elements, left, middle - 1, element);
    return binarySearch(elements, middle + 1, right, element);
  }

  return -1;
}

int lookForElementInArrayOfTeams(Team *data[], int numberOfTeams, int element) {
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

  elementsLoop(data, numberOfTeams);

  printf("%d\n", lookForElementInArrayOfTeams(data, numberOfTeams, 60));
}
