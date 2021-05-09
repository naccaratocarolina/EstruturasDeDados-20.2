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

static int getMaxNumber(int a, int b) {
	return (a > b)? a : b;
}

static Node *createNewNode(int value) {
	Node *newNode = (Node*) malloc(sizeof(Node));

	// Inicializa as variaveis da arvore AVL
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->levels = 1;
	return newNode;
}

static int getNumberOfLevels(Node *node) {
	// se a arvore estiver vazia
	if (node == NULL) return 0;

	return node->levels;
}

// Uma sub-arvore esta desequilibrada quando o resultado dessa funcao eh maior do que 1
// ou menor do que -1
// Toleramos numeros de desequilibrio de 0, 1 e -1
static int getImbalanceFactor(Node *node) {
	// se a arvore estiver vazia
	if (node == NULL) return 0;

	// Encontramos o equilibrio da arvore subtraindo o numeros de niveis
	// na sub-arvore da esquerda do numero de niveis da sub-arvore da direita
	return getNumberOfLevels(node->left) - getNumberOfLevels(node->right);
}

Node *leftRotation(Node *root) {
 Node *x = root->right; // filho da direita da root atual (nova raiz)
 Node *y = x->left; // filho da esquerda do filho da direita da root

 // Raiz atual vira o filho da esquerda do seu filho da direita
 x->left = root;

 // Filho da esquerda do filho da direita da raiz vira o filho da direita da nova posicao da raiz
 root->right = y;

 // Atualiza o numero de niveis
 root->levels = getMaxNumber(getNumberOfLevels(root->left), getNumberOfLevels(root->right)) + 1;
 x->levels = getMaxNumber(getNumberOfLevels(x->left), getNumberOfLevels(x->right)) + 1;

 // retorna a nova raiz
 return x;
}

Node *rightRotation(Node *root) {
	Node *x = root->left; // filho da esquerda da root atual (nova raiz)
	Node *y = x->right; // filho da direita do filho da esquerda da root

	// Raiz atual vira o filho da direita do seu filho da esquerda
	x->right = root;

	// Filho da direita do filho da esquerda da raiz vira o filho da esquerda da nova posicao da raiz
	root->left = y;

	// Atualiza o numero de niveis
	root->levels = getMaxNumber(getNumberOfLevels(root->left), getNumberOfLevels(root->right)) + 1;
  x->levels = getMaxNumber(getNumberOfLevels(x->left), getNumberOfLevels(x->right)) + 1;

	return x;
}

Node *insert(Node *node, int value) {
	// Se a arvore estiver vazia, nao ha restricoes para insercao do novo no
	if (node == NULL) return (createNewNode(value));
	
	// Se o valor a ser inserido for menor que o valor guardado no no, inserta a esquerda
	if (value < node->value) node->left = insert(node->left, value);
	
	// Se o valor a ser inserido for maior que o valor guardado no no, inserta a direita
	else if (value > node->value) node->right = insert(node->right, value);

	// Nao eh permitido inserir valores iguais na arvore
	else return node;

	// Atualiza numero de niveis
	node->levels = 1 + getMaxNumber(getNumberOfLevels(node->left), getNumberOfLevels(node->right));

	// Encontra o fator de desequilibrio da arvore
	int imbalanceFactor = getImbalanceFactor(node);

	if (imbalanceFactor > 1 && value < node->left->value) return rightRotation(node);

	if (imbalanceFactor > -1 && value > node->right->value) return leftRotation(node);

	if (imbalanceFactor > 1 && value > node->left->value) {
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}

	if (imbalanceFactor < -1 && value < node->right->value) {
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}

	return node;
}

void printTreeInOrder(Node *root) {
	if (root != NULL) {
		printf("%d\n", root->value);
		printTreeInOrder(root->left);
		printTreeInOrder(root->right);
	}
}

void printTreeInReverseOrder(Node *root) {
	if (root != NULL) {
		printTreeInReverseOrder(root->right);
		printf("%d\n", root->value);
		printTreeInReverseOrder(root->left);
	}
}

int main (int argc, char *argv[]) {
	Node *root = NULL;
	int newNode;

	// Loop principal que le os numeros do arquivo de entrada
	while (1 == scanf("%d", &newNode)) {
		root = insert(root, newNode);
	}

	//printTreeInReverseOrder(root);
}
