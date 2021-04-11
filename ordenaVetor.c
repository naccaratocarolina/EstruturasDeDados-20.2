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

int* dynamicallyFillArray(FILE *numbersFile, int* arraySize, int* arrayOfNumbers) {
	int size = 0;
	int temporaryNumber;
	char c;

	for (c = getc(numbersFile); c != EOF; c = getc(numbersFile)) {
		fscanf(numbersFile, "%d", &temporaryNumber);

		int *newArrayOfNumbers = realloc(arrayOfNumbers, ++size * sizeof *newArrayOfNumbers);
		
		arrayOfNumbers = newArrayOfNumbers;
		newArrayOfNumbers[size - 1] = temporaryNumber;
	}

	*arraySize = size;

	return arrayOfNumbers;
}

int main (int argc, char *argv[]) {
	char algorithm[10];
	FILE *numbersFile;
	int* arrayOfNumbers = NULL;
	int arraySize;

	// Verifica se recebeu os argumentos de entrada
	if (argc < 2) {
		printf("Voce nao inseriu todos os argumentos necessarios!");
		return 1;
	}

	// Abre o arquivo de entrada e verifica sucesso
	numbersFile = fopen(argv[1], "r");
	if (numbersFile == NULL) {
		printf("Erro de abertura do arquivo de entrada (%s)\n", argv[1]);
		return 2;
	}

	arrayOfNumbers = dynamicallyFillArray(numbersFile, &arraySize, arrayOfNumbers);

	for (int i=0; i<arraySize; i++) {
		printf("%d\n", arrayOfNumbers[i]);
	}

	// Preenche o algoritmo confirme o parametro dado
	if (argv[2]) strcpy(algorithm, argv[2]);
	
	// Seleciona o algoritmo desejado
	if (algorithm[1] == 'q') quickSort();
	else if (algorithm[1] == 'm') mergeSort();
	else quadraticAlgorithm();

	free(arrayOfNumbers);

	return(0);
}
