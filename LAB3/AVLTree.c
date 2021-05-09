#include<stdio.h>
#include<stdlib.h>

// Estrutura de dados que vai representar a arvore AVL
struct Node {
	int value; // valor guardado no no
	int levels; // numero de niveis
	struct Node *left; // elemento da sub-arvore da esquerda
	struct Node *right; // elemento da sub-arvore da direita
};
typedef struct Node Node;

static Node *createNewNode(int value) {
	Node *newNode = (Node*) malloc(sizeof(Node));

	// Inicializa as variaveis da arvore AVL
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->levels = 1;
	return newNode;
}

static int findNumberOfLevels(Node *node) {
	// se a arvore estiver vazia
	if (node == NULL) return 0;

	return node->levels;
}

static int findBalance(Node *node) {
	// se a arvore estiver vazia
	if (node == NULL) return 0;

	// Encontramos o equilibrio da arvore subtraindo o numeros de niveis
	// na sub-arvore da esquerda do numero de niveis da sub-arvore da direita
	return findNumberOfLevels(node->left) - findNumberOfLevels(node->right);
}

int main (int argc, char *argv[]) {
	int newNode;

	// Loop principal que le os numeros do arquivo de entrada
	while (1 == scanf("%d", &newNode)) {
		printf("%d\n", newNode);
	}
}
