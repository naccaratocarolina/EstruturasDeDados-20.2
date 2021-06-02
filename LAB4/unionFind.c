#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct UF { // Union Find
	int* p;
	int* rank;
	int* size;
	int numberOfSets;
};
typedef struct UF UF;

UF *createUnionFindDisjointSet(int numberOfSets) {
	// Aloca espaco para a estrutura de dados
	UF *newUf = (UF*) malloc(sizeof(UF));
/*
	// Verifica se houve erro de alocacao de memoria
	if (!newUf) {
		printf("Erro de alocacao de memoria.\n");
		exit(0);
	}

	// Inicializa as propriedades
	newUf->numberOfSets = numberOfSets;
	newUf->p = (int*) malloc(sizeof(int) * numberOfSets);
	newUf->rank = (int*) malloc(sizeof(int) * numberOfSets);
	for (int i=0; i<numberOfSets; i++) {
		newUf->p[i] = i;
	}
	newUf->size = (int*) malloc(sizeof(int) * numberOfSets - 1);*/

	return newUf;
}

int findSet(int i, UF *uf) {
	if (uf->p[i] == i) return i;
	return uf->p[i] = findSet(uf->p[i], uf);
}

bool isSameSet(int i, int j, UF *uf) {
	return findSet(i, uf) == findSet(j, uf);
}

void unionFind(int i, int j, UF *uf) {
	if (!isSameSet(i, j, uf)) {
		int x = findSet(i, uf);
		int y = findSet(j, uf);

		if (uf->rank[x] > uf->rank[y]) {
			uf->p[y] = x;
			uf->size[findSet(x, uf)] += uf->size[findSet(y, uf)];
		} else {
			uf->p[x] = y;
			if (uf->rank[x] == uf->rank[y]) uf->rank[y]++;
			uf->size[findSet(y, uf)] += uf->size[findSet(x, uf)];
		}
		uf->numberOfSets--;
	}
}

int numberOfDisjoinSets(UF *uf) {
	return uf->numberOfSets;
}

int main (int argc, char *argv[]) {
	int n;
	int m;
	int count = 1;
	int u;
	int v;

	while (scanf("%d %d", &n, &m), n || m) {
		//UF *uf = createUnionFindDisjointSet(n);
/*
		for (int i=0; i<m; i++) {
			scanf("%d %d", &u, &v);
			u--;
			v--;
			unionFind(u, v, uf);
		}

		printf("adasd");
		printf("Case %d: %d\n", count++, numberOfDisjoinSets(uf));*/
	}

	return 0;
}
