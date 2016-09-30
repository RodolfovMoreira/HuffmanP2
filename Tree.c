#include "HuffmanLibrary.h"

typedef struct Node{
	unsigned char item;
	int priority;
	int flag;
	struct Node *next_node;
	struct Node *previous_node;
	struct Node *left;
	struct Node *right;
}Node;

Node* sort_tree(Node *root)
{
	while(root -> next_node != NULL && root -> priority > root -> next_node -> priority) // ENQUANTO NÃO CHEGAR AO FIM DA LISTA E ENQUANTO SUA PRIORIDADE FOR MAIOR //
	{
		if(root -> next_node -> next_node != NULL)
		{
			root -> next_node -> next_node -> previous_node = root;
		}

		if(root -> previous_node != NULL)
		{
			root -> previous_node ->next_node = root -> next_node;
		}

		root -> next_node -> previous_node = root ->previous_node;
		root -> previous_node = root -> next_node;
		root -> next_node = root -> next_node -> next_node;
		root -> previous_node -> next_node = root;
	}

	while(root -> previous_node != NULL)
	{
		root = root -> previous_node; // PROCURA A CABEÇA PARA RETORNAR //
	}

	return root;
}

Node* merge_nodes(Node *first)
{
	Node *root = (Node*) malloc(sizeof(Node));  // CRIA RAIZ PARA AGRUPAR DOIS NODES //

	root -> item = '*'; // CHAR DE REPRESENTAÇÃO //
	root -> priority = (first -> priority + first -> next_node -> priority); // SOMA AS PRIORIDADES DOS DOIS MENORES //
	root -> flag = 0;
	root -> next_node = NULL;
	root -> previous_node = NULL;

	if(first -> next_node -> next_node != NULL)
	{
		root -> next_node = first -> next_node -> next_node; // SE HOUVER UM TERCEIRO NODE, FAZ ROOT RECONHECE-LO //
	}

	root -> left = first; // LEFT PEGA O MENOR //
	root -> right = first -> next_node; // RIGHT PEGA O PRÓXIMO //

	root -> left -> next_node = NULL; // SETA OS PONTEIROS DE CADA NODE AGRUPADO PARA NULL, FORMANDO A ÁRVORE //
	root -> left -> previous_node = NULL;
	root -> right -> next_node = NULL;
	root -> right -> previous_node = NULL;

	return root; // RETORNA A RAIZ PARA O FIRST NA MAIN //
}

int tree_size(Node *tree, int size)
{
	size++;

	if(tree->left != NULL)
	{
		size = tree_size(tree->left, size);
	}

	if(tree->right != NULL)
	{
		size = tree_size(tree->right, size);
	}

	return size;
}

Node* make_tree(Node *root) //ORDENAR NODES DA ARVORE ENQUANTO FAZ O MERGE
{
	while(root -> next_node != NULL) // SÓ CHAMA A FUNÇÃO SE HOUVER MAIS DE UM NODE SOBRANDO //
	{
		root = merge_nodes(root);
		root = sort_tree(root);
	}

	return root;
}

void print_pre_order(Node *tree, FILE *printing)
{
	if(tree != NULL)
	{
		fprintf(printing, "%u", tree->item); // Imprime cada unsigned no arquivo de saída

		if(tree->flag) // SE A FLAG ESTIVER SETADA (ESCAPE DO CONTRA BARRA) IMPRIME NOVAMENTE PARA DIFERENCIAR NA DESCOMPRESSAO (MONTAGEM DA ÁRVORE)
		{
			fprintf(printing, "%u", tree->item);
		}

		if(tree->left != NULL)
		{
			print_pre_order(tree->left, printing);
		}

		if(tree->right != NULL)
		{
			print_pre_order(tree->right, printing);
		}
	}
}
