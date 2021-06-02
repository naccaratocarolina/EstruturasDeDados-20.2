#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Set {
	// vetor de elementos parentais
	// parent[i] eh o pai do ith elemento
	int *parent;

	// vetor de alturas
	// rank[i] eh a altura da arvore que representa o conjunto
	int *rank;

	int *setSize;

	// Numero de conjuntos (sets) da Union Find
	int numberOfSets;
};
typedef struct Set Set;

void createNewSet(int numberOfSets, Set *set) {
	for (int i=0; i<numberOfSets; i++) {
		set->parent[i] = i;
	}
}

Set *initializeSet(int numberOfSets) {
	Set *newSet = (Set*) malloc(sizeof(Set));
	newSet->numberOfSets = numberOfSets;
	newSet->parent = (int*) malloc(sizeof(int) * numberOfSets);
	newSet->rank = (int*) malloc(sizeof(int) * numberOfSets);
	createNewSet(numberOfSets, newSet);
	newSet->setSize = (int*) malloc(sizeof(int) * (numberOfSets - 1));

	return newSet;
}

int find(int i, Set *set) {
	if (set->parent[i] != i) set->parent[i] = find(set->parent[i], set);
	return i;
}

void Union(int x, int y, Set *set) {
	int xset = find(x, set);
	int yset = find(y, set);

	if (xset == yset) return;

	if (set->rank[xset] < set->rank[yset]) {
		set->parent[xset] = yset;
		set->setSize[yset] += set->setSize[xset];
	}

	else if (set->rank[xset] > set->rank[yset]) {
		set->parent[yset] = xset;
		set->setSize[xset] += set->setSize[yset];
	} 

	else {
		set->rank[yset]++;
		set->setSize[yset] += set->setSize[xset];
	}

	set->numberOfSets--;
}

int main (int argc, char *argv[]) {
	int n, m, count = 1;
	int u, v;

	while (scanf("%d %d", &n, &m), n || m) {
		Set *set = initializeSet(n);
		
		for (int i=0; i<m; i++) {
			scanf("%d %d", &u, &v);
			u--;
			v--;
			Union(u, v, set);
		}

		printf("Case %d: %d\n", count++, set->numberOfSets);
	}

	return 0;

}
