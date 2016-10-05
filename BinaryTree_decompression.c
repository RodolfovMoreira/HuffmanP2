/*BINARYTREE_DECOMPRESSION:

  Biblioteca da árvore usada na descompressão, árvore será criada a partir da leitura do arquivo compactado ".huff"

TYPEDEF STRUCT BINARYTREE :
Nó que será usado na biblioteca. Está estruturado em:
Unsigned char item, int flag, struct BinaryTree *left, struct BinaryTree *right.

-Funções-

BINARYTREE* CREATE_EMPTY_TREE() :
Retorna NULL, inicializando a árvore.

BINARYTREE* CREATE_BT_NODE(UNSIGNED CHAR ITEM, INT FLAG) :
Cria um nó na árvore.*/

#include "Huff_Library.h"



typedef struct BinaryTree{
	unsigned char item;
	int flag;
	struct BinaryTree *left;
	struct BinaryTree *right;
}BinaryTree;

BinaryTree* create_empty_tree(){
	return NULL;
}

BinaryTree* create_bt_node(unsigned char item, int flag)
{
	BinaryTree *newbt = (BinaryTree*) malloc(sizeof(BinaryTree));
	newbt -> item = item;
	newbt -> flag = flag;
	newbt -> left = NULL;
	newbt -> right = NULL;

	return newbt;
}

