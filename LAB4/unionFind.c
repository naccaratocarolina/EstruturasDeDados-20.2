#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct UnionFind {
	// vetor de elementos parentais
	// parent[i] eh o pai do ith elemento
	int *parent;

	// vetor de alturas
	// rank[i] eh a altura da arvore que representa o conjunto
	int *rank;

	int *setSize;

	// Numero de conjuntos (unionFinds) da Union Find
	int numberOfUnionFinds;
};
typedef struct UnionFind UnionFind;

void createNewUnionFind(int numberOfUnionFinds, UnionFind *unionFind) {
	for (int i=0; i<numberOfUnionFinds; i++) {
		unionFind->parent[i] = i;
		unionFind->setSize[i] = 1;
	}
}

UnionFind *initializeUnionFind(int numberOfUnionFinds) {
	UnionFind *newUnionFind = (UnionFind*) malloc(sizeof(UnionFind));
	newUnionFind->numberOfUnionFinds = numberOfUnionFinds;
	newUnionFind->parent = (int*) malloc(sizeof(int) * numberOfUnionFinds);
	newUnionFind->rank = (int*) malloc(sizeof(int) * numberOfUnionFinds);
	newUnionFind->setSize = (int*) malloc(sizeof(int) * numberOfUnionFinds);
	createNewUnionFind(numberOfUnionFinds, newUnionFind);

	return newUnionFind;
}

int find(int i, UnionFind *unionFind) {
	if (unionFind->parent[i] != i) unionFind->parent[i] = find(unionFind->parent[i], unionFind);
	return i;
}

bool isSameUnionFind(int i, int j, UnionFind *unionFind) {
	return find(i, unionFind) == find(j, unionFind);
}

void Union(int x, int y, UnionFind *unionFind) {
	// Encontra o set dos elementos
	int xset = find(x, unionFind);
	int yset = find(y, unionFind);

	// Se eles ja estiverem no mesmo set
	if (xset == yset) return;

	// Coloca o elemento de rank menor abaixo
	// do elemento de rank maior
	if (unionFind->rank[xset] < unionFind->rank[yset]) {
		unionFind->parent[xset] = yset;
		unionFind->setSize[yset] += unionFind->setSize[xset];
	}

	else if (unionFind->rank[xset] > unionFind->rank[yset]) {
		unionFind->parent[yset] = xset;
		unionFind->setSize[xset] += unionFind->setSize[yset];
	}

	// Se os ranks forem iguais, incrementar o rank
	else {
		unionFind->parent[yset] = xset;
		unionFind->rank[xset] = unionFind->rank[xset] + 1;
	}

	unionFind->numberOfUnionFinds--;

}

int main (int argc, char *argv[]) {
	int n, m, count = 1;
	int u, v;

	while (scanf("%d %d", &n, &m), n || m) {
		UnionFind *unionFind = initializeUnionFind(n);
		
		for (int i=0; i<m; i++) {
			scanf("%d %d", &u, &v);
			u--;
			v--;
			Union(u, v, unionFind);
		}

		printf("Case %d: %d\n", count++, unionFind->numberOfUnionFinds);
		free(unionFind);
	}

	return 0;

}
