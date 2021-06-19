#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct UnionFind {
	// vetor de elementos que representam os conjuntos
	// parent[i] eh o representante do ith elemento
	int *parent;

	// vetor de alturas
	// rank[i] eh a altura da arvore que representa o conjunto
	int *rank;

	// Numero de conjuntos (sets) da Union Find
	int sets;
};
typedef struct UnionFind UnionFind;

void initializeSet(int sets, UnionFind *unionFind) {
	for (int i=0; i<sets; i++) {
		unionFind->parent[i] = i;
		unionFind->rank[i] = 0;
	}
}

UnionFind *initializeUnionFind(int sets) {
	// Aloca espaco para a estrutura de dados
	UnionFind *newUnionFind = (UnionFind*) malloc(sizeof(UnionFind));

	// Verifica erros
	if (!newUnionFind) {
		printf("Erro de alocacao de memoria.\n");
		exit(0);
	}

	// Inicializa variaveis
	newUnionFind->sets = sets;
	newUnionFind->parent = (int*) malloc(sizeof(int) * sets);
	newUnionFind->rank = (int*) malloc(sizeof(int) * sets);
	initializeSet(sets, newUnionFind);

	// Verifica erros
	if (!newUnionFind->parent || !newUnionFind->rank) {
		printf("Erro de alocacao de memoria.\n");
		exit(0);
	}

	return newUnionFind;
}

int find(int i, UnionFind *unionFind) {
	// Se i nao eh o pai de si mesmo, entao i nao eh o representante do seu conjunto
	if (unionFind->parent[i] != i) 
		// Nesse caso, fazemos uma chamada recursiva de find e movemos o noh i diretamente
		// sob o representante do seu conjunto, ate encontrarmos o ultimo
		unionFind->parent[i] = find(unionFind->parent[i], unionFind);

	return unionFind->parent[i];
}

void Union(int x, int y, UnionFind *unionFind) {
	// Encontra o representante dos sets dos elementos dados
	int xset = find(x, unionFind);
	int yset = find(y, unionFind);

	// Se eles ja estiverem no mesmo set nao faz nada
	if (xset == yset) return;

	// Coloca o elemento de rank menor abaixo do elemento de rank maior, 
	// de forma que o set de maior rank se torna o representante do de menor rank
	if (unionFind->rank[xset] < unionFind->rank[yset]) {
		unionFind->parent[xset] = yset;
	}

	else if (unionFind->rank[xset] > unionFind->rank[yset]) {
		unionFind->parent[yset] = xset;
	}

	// Se os ranks forem iguais, incrementar o rank e fazer com que o representante
	// de y seja o representante de x tambem
	else {
		unionFind->parent[yset] = xset;
		unionFind->rank[xset] = unionFind->rank[xset] + 1;
	}
	
	// Decrementa a quantidade de sets armazenada pois se chegou ate aqui significa 
	// que dois conjuntos foram unidos (se refere a quantidade de religioes)
	unionFind->sets--;
}

int main (int argc, char *argv[]) {
	int n, m, count = 1;
	int u, v;

	while (1) {
		// Le e armazena as informacoes de n e m
		scanf("%d %d", &n, &m);

		// Criterio de parada: n = 0
		if (n == 0) break;

		// Inicializa a estrutura de dados
		UnionFind *unionFind = initializeUnionFind(n);

		for (int i=0; i<m; i++) {
			// Le os pares dados, representados por u e v
			scanf("%d %d", &u, &v);

			// Realiza a operacao union find da estrutura
			Union(u, v, unionFind);
		}

		// Printa o resultado e incrementa o numero de casos
		printf("Case %d: %d\n", count++, unionFind->sets);

		// Libera o espaco do ponteiro
		free(unionFind);
	}

	return 0;

}
