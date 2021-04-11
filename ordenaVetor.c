#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void  quickSort() {
	printf("quick sort");
}

void mergeSort() {
	printf("merge sort");
}

void quadraticAlgorithm() {
	printf("quadratico");
}

int* dynamicallyFillArray(int* arrayOfNumbers) {
	int size = 0;
	int temporaryNumber;

	while (1 == scanf("%d", &temporaryNumber)) {
		int *newArrayOfNumbers = realloc(arrayOfNumbers, ++size * sizeof *newArrayOfNumbers);
		
		arrayOfNumbers = newArrayOfNumbers;
		newArrayOfNumbers[size - 1] = temporaryNumber;
	}

	return arrayOfNumbers;
}

int main () {
	char algorithm[10];
	char q = 'q', m = 'm';
	int* arrayOfNumbers = NULL;

  printf("Informe o algoritmo: ");
  fgets(algorithm, 10, stdin);

  printf("%c", algorithm[1]);
	if (algorithm[1] == q) quickSort();
	else if (algorithm[1] == m) mergeSort();
	else quadraticAlgorithm();

	arrayOfNumbers = dynamicallyFillArray(arrayOfNumbers);
	free(arrayOfNumbers);

	return(0);
}
