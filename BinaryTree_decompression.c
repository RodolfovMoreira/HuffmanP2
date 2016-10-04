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

/*BinaryTree* remake_tree(BinaryTree *bt, unsigned char *string, int size, int backslash, int ni)
{
	int index;

	if(ni == 0){
		ni = 1;
		index = 0;
	}

	if(index == size+1) // Retorna se chegar ao fim da lista da árvore
	{
		return bt;
	}

	else
	{
		if(string[index] == '*') // Se achar '*', vai para esquerda e depois para direita
		{
			bt = create_bt_node(string[index], 0);
			index++;
			bt->left = remake_tree(bt->left, string, size, backslash, ni);
			index++;
			bt->right = remake_tree(bt->right, string, size, backslash, ni);
		}

		else // Caso um char qualquer, cria folha e retorna
		{
			if(string[index] == '\\' && index == backslash) // Verifica se está no '\' real, se for, aciona a flag
			{
				bt = create_bt_node(string[index], 1);
				return bt;
			}

			else
			{
				bt = create_bt_node(string[index], 0);
				return bt;
			}
		}
	}

	return bt;
}*/
