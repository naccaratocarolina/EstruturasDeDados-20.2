#include <stdio.h>
#include <stdlib.h>

int getParent(int i, int *set) {
	if (i == set[i])
		return i;

	else return (set[i] = getParent(set[i], set));
}

int isUnion(int x, int y, int *set) {
	return getParent(x, set) == getParent(y, set);
}

void Union(int x, int y, int *set) {
	set[getParent(x, set)] = getParent(y, set);
}

int main(int argc, char *argv[]) {
	int c, u, v, n, m;

	scanf("%d %d", &n, &m);
	c = 1;
	
	while(n || m) {
		for (int i=0; i<=n; i++) {
			set[i] = i;
		}

		while (m--) {

		}
	}
}
