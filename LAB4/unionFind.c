#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Set {
	// vetor de elementos parentais
	// parent[i] eh o pai do ith elemento
	int *parent;

	// vetor de alturas
	// height[i] eh a altura da arvore que representa o conjunto
	int *height;

	// Numero de elementos da Union Find
	int items;
};
typedef struct Set Set;

void createNewSet(int items, Set *set) {
	for (int i=0; i<items; i++) {
		set->parent[i] = i;
	}
}

Set *initializeSet(int items) {
	Set *newSet = (Set*) malloc(sizeof(Set));
	newSet->items = items;
	newSet->parent = (int*) malloc(sizeof(int) * items);
	newSet->height = (int*) malloc(sizeof(int) * items);
	createNewSet(items, newSet);

	return newSet;
}

int find(int i, Set *set) {
	if (set->parent[i] != i) set->parent[i] = find(set->parent[i], set);
	return set->parent[i];
}

void Union(int x, int y, Set *set) {
	int xset = find(x, set);
	int yset = find(y, set);

	if (xset == yset) return;

	if (set->height[xset] < set->height[yset])
		set->parent[xset] = yset;
	else if (set->height[xset] > set->height[yset])
		set->parent[yset] = xset;
	else {
		set->parent[yset] = xset;
		set->height[xset] = set->height[xset] + 1;
	}
}

int main (int argc, char *argv[]) {
	int n, m, count = 1;
	int u, v;
	
	while (scanf("%d %d", &n, &m), n || m) {
		Set *set = initializeSet(10);
		
		for (int i=0; i<m; i++) {
			scanf("%d %d", &u, &v);
			u--;
			v--;
			Union(u, v, set);
		}

		//printf("Case %d: %d", count++, set->items);
	}

	return 0;
}
