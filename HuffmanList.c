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

Node* create_linked_list(){ // Inicializando lista encadeada
	return NULL;
}

Node* insert_item(Node *node, unsigned char item, int priority) // Função de criação e inserção de novo nó na lista
{
	Node *newnode = (Node*) malloc(sizeof(Node));

	newnode -> item = item;
	newnode -> priority = priority;
	newnode -> flag = 0;
	newnode -> next_node = node;
	newnode -> previous_node = NULL;

	//---------------- Flags que resolvem o problema do coringa ---------------

	if(item == '\\')
	{
		newnode -> flag = 1; // Marcação de caractere de escape
	}

	else if(item == '*')
	{
		newnode -> item = '\\'; // Caractere de escape para diferenciar de asterisco da árvore
	}

	// -------------------------------------------------------------------------

	if(newnode -> next_node != NULL)
	{
		newnode -> next_node -> previous_node = newnode; // Setando o 'previously'
	}

	//------- Setando ponteiros das árvores ---

	newnode -> left = NULL;
	newnode -> right = NULL;

	// ----------------------------------------

	return newnode;
}

void bubble_sort(Node *first)
{
	char aux_item;
	int aux_priority, aux_flag;

	Node *hold;
	Node *current;

	for(hold = first; hold != NULL; hold = hold -> next_node)
	{
		for(current = hold; current != NULL; current = current -> next_node)
		{
			if(hold -> priority > current -> priority)
			{
				aux_item = hold -> item;
				aux_priority = hold -> priority;
				aux_flag = hold -> flag;
				hold -> item = current -> item;
				hold -> priority = current -> priority;
				hold -> flag = current -> flag;
				current -> item = aux_item;
				current -> priority = aux_priority;
				current -> flag = aux_flag;
			}
		}
	}
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

