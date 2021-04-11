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

void merge(int* arrayOfNumbers, int start, int middle, int end) {
	int n1 = middle - start + 1;
	int n2 = end - middle;

	int tempArray1[n1], tempArray2[n2];

	for (int i=0; i<n1; i++) {
		tempArray1[i] = arrayOfNumbers[start + i];
	}

	for (int j=0; j<n2; j++) {
		tempArray2[j] = arrayOfNumbers[middle + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = start;
	
	while (i < n1 && j < n2) {
		if (tempArray1[i] <= tempArray2[j]) {
			arrayOfNumbers[k] = tempArray1[i];
			i += 1;
		}

		else {
			arrayOfNumbers[k] = tempArray2[j];
			j += 1;
		}
		k += 1;
	}

	while (i < n1) {
		arrayOfNumbers[k] = tempArray1[i];
		i += 1;
		k += 1;
	}

	while (j < n2) {
		arrayOfNumbers[k] = tempArray2[j];
		j += 1;
		k += 1;
	}
}

void mergeSort(int* arrayOfNumbers, int start, int end) {
	if (start < end) {
		int middle = (start + end)/2;
		mergeSort(arrayOfNumbers, start, middle);
		mergeSort(arrayOfNumbers, middle + 1, end);
		merge(arrayOfNumbers, start, middle, end);
	}
}

void bubbleSort(int* arrayOfNumbers, int arraySize) {
	for (int i=1; i<arraySize; i++) {
		for (int j=0; j<arraySize-i; j++) {
			if (arrayOfNumbers[j] > arrayOfNumbers[j + 1]) {
				exchange(&arrayOfNumbers[j], &arrayOfNumbers[j+1]);
			}
		}
	}
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

	// Seleciona o algoritmo desejado
	if (argc == 1) bubbleSort(arrayOfNumbers, arraySize);
	else {
		if (strcmp(argv[1], "-q") == 0) quickSort(arrayOfNumbers, 0, arraySize - 1);
		else if (strcmp(argv[1], "-m") == 0) mergeSort(arrayOfNumbers, 0, arraySize - 1);
	}
	
	printArrayOfNumbers(arrayOfNumbers, arraySize);
	
	free(arrayOfNumbers);

	return(0);
}
