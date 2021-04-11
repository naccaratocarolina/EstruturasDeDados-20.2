#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void exchange(int* firtsElement, int* secondElement) {
	int temporaryNumber = *firtsElement;
	*firtsElement = *secondElement;
	*secondElement = temporaryNumber;
}

int partition(int* arrayOfNumbers, int start, int end) {
	int pivot = arrayOfNumbers[end];
	int i = (start - 1);

	for (int j=start; j<=end - 1; j++) {
		if (arrayOfNumbers[j] <= pivot) {
			i += 1;
			exchange(&arrayOfNumbers[i], &arrayOfNumbers[j]);
		}
	}
	
	exchange(&arrayOfNumbers[i + 1], &arrayOfNumbers[end]);
	return (i + 1);
}

void  quickSort(int* arrayOfNumbers, int start, int end) {
	if (start < end) {
		int part = partition(arrayOfNumbers, start, end);
		quickSort(arrayOfNumbers, start, part - 1);
		quickSort(arrayOfNumbers, part + 1, end);
	}
}

void mergeSort() {
	printf("merge sort");
}

void quadraticAlgorithm() {
	printf("quadratico");
}

void printArrayOfNumbers(int* arrayOfNumbers, int arraySize) {
	for (int i=0; i<arraySize; i++) {
		printf("%d\n", arrayOfNumbers[i]);
	}
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
	printArrayOfNumbers(arrayOfNumbers, arraySize);

	// Seleciona o algoritmo desejado
	if (argc == 1) quadraticAlgorithm();
	else {
		if (strcmp(argv[1], "-q") == 0) quickSort(arrayOfNumbers, 0, arraySize - 1);
		else if (strcmp(argv[1], "-m") == 0) mergeSort();
	}
	
	printf("%s", "\n");
	printArrayOfNumbers(arrayOfNumbers, arraySize);
	
	free(arrayOfNumbers);

	return(0);
}
