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

int* dynamicallyFillArray(int* arraySize, int* arrayOfNumbers) {
	int size = 0;
	int numberPerLine;

	while (1 == scanf("%d", &numberPerLine)) {
		int *newArrayOfNumbers = realloc(arrayOfNumbers, ++size * sizeof *newArrayOfNumbers);
		
		arrayOfNumbers = newArrayOfNumbers;
		newArrayOfNumbers[size - 1] = numberPerLine;
	}
	*arraySize = size;

	return arrayOfNumbers;
}

int main (int argc, char *argv[]) {
	int* arrayOfNumbers = NULL;
	int arraySize;

	arrayOfNumbers = dynamicallyFillArray(&arraySize, arrayOfNumbers);

	for (int i=0; i<arraySize; i++) {
		printf("%d\n", arrayOfNumbers[i]);
	}
	
	printf("%s", argv[1]);
	// Seleciona o algoritmo desejado
	if (argc == 1) quadraticAlgorithm();
	else {
		if (strcmp(argv[1], "-q") == 0) quickSort();
		else if (strcmp(argv[1], "-m") == 0) mergeSort();
	}

	free(arrayOfNumbers);

	return(0);
}
