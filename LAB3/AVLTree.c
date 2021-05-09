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

Node *createNewNode(int value) {
	Node *newNode = (Node*) malloc(sizeof(Node));

	// Inicializa as variaveis da arvore AVL
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->levels = 1;
	return newNode;
}

int getMaxNumber(int a, int b) {
	return (a > b)? a : b;
}

int getLevels(Node *node) {
	// se a arvore estiver vazia
	if (node == NULL) return 0;

	// caso contrario, retorna a propriedade levels do no dado
	return node->levels;
}

int getBalanceFactor(Node *node) {
	// se a arvore estiver vazia
	if (node == NULL) return 0;

	// Encontramos o equilibrio da arvore subtraindo o numeros de niveis
	// na sub-arvore da esquerda do numero de niveis da sub-arvore da direita
	return getLevels(node->left) - getLevels(node->right);
}

int updateLevels(Node *node) {
	return getMaxNumber(getLevels(node->left), getLevels(node->right)) + 1;
}

Node *singleLeftRotation(Node *x) {
	Node *y = x->right; // filho da direita da root atual (nova raiz)
	Node *z = y->left; // filho da esquerda do filho da direita da root

	// Raiz atual vira o filho da esquerda do seu filho da direita
  y->left = x;

	// Filho da esquerda do filho da direita da raiz vira o filho da direita da nova posicao da raiz
	x->right = z;

	// Atualiza o numero de niveis
  x->levels = updateLevels(x);
	y->levels = updateLevels(y);

	// retorna a nova raiz
  return y;
}

Node *singleRightRotation(Node *y) {
	Node *x = y->left; // filho da esquerda da root atual (nova raiz)
	Node *z = x->right; // filho da direita do filho da esquerda da root

	// Raiz atual vira o filho da direita do seu filho da esquerda
	x->right = y;

	// Filho da direita do filho da esquerda da raiz vira o filho da esquerda da nova posicao da raiz
	y->left = z;

	// Atualiza o numero de niveis
	y->levels = updateLevels(y);
	x->levels = updateLevels(x);

	// retorna a nova raiz
	return x;
}

Node *doubleLeftRotation(Node *x) {
	x->right = singleRightRotation(x->right);
	return singleLeftRotation(x);
}

Node *doubleRightRotation(Node *y) {
	y->left =  singleLeftRotation(y->left);
	return singleRightRotation(y);
}

Node* insert(Node *node, int value) {
	// Se a arvore estiver vazia, inserta um novo no sem restricoes
	if (node == NULL) return(createNewNode(value));

	// Realiza a insercao de novos nos conforme o algoritmo de uma arvore BST
	if (value < node->value) node->left  = insert(node->left, value);
	else if (value > node->value) node->right = insert(node->right, value);
	else return node;

	// Atualiza o numero de niveis
	node->levels = updateLevels(node);

	// Uma sub-arvore esta desequilibrada quando o resultado dessa funcao
	// eh maior que 1 ou menor que -1. Nesses casos, temos que corrigir
	// o desequilibrio realizando as rotacoes
	int balance = getBalanceFactor(node);

	if (balance > 1) {
		if (value < node->left->value) return singleRightRotation(node);
		else if (value > node->left->value) return doubleRightRotation(node);
	}

	if (balance < -1) {
		if (value > node->right->value) return singleLeftRotation(node);
		else if (node->right->value) return doubleLeftRotation(node);
	}

	return node;
}

void freeAVLTree(Node *node) {
	if (node != NULL) {
		freeAVLTree(node->left);
		freeAVLTree(node->right);
		free(node);
	}
}

void printTreeInOrder(Node *root) {
	if (root != NULL) {
		printf("%d\n", root->value);
		printTreeInOrder(root->left);
		printTreeInOrder(root->right);
	}
}

int main (int argc, char *argv[]) {
	Node *root = NULL;
	int createNewNode;

	// Loop principal que le os numeros do arquivo de entrada
	while (1 == scanf("%d", &createNewNode)) {
		// A cada valor lido, insertar na arvore AVL
		root = insert(root, createNewNode);
	}
	
	// Faz o display da arvore AVL em pre ordem
	printTreeInOrder(root);

	// Libera o espaco alocado
	freeAVLTree(root);
}
