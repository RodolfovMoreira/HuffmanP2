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

