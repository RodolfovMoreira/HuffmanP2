/*LINKEDLIST

  Biblioteca de uma lista utilizada no projeto.

TYPEDEF STRUCT NODE : Ver estrutura em 'BinaryTree_compression'

-Funções-

NODE* CREATE_LINKED_LIST():
Função que inicializa a lista.

NODE* INSERT_ITEM(NODE *NODE, UNSIGNED CHAR ITEM, INT PRIORITY):
Função que cria um nó e insere na lista.

NODE* CHAR_LIST(NODE *LIST, INT *FREQUENCY):
Função que captura as frequências e cria uma lista dos caracteres.

VOID BUBBLE_SORT(NODE *FIRST):
Função que ordena a lista de acordo com as frequências.*/
#include "Huff_Library.h"

typedef struct Node{
	unsigned char item;
	int priority;
	int flag;
	struct Node *next_node;
	struct Node *previous_node;
	struct Node *left;
	struct Node *right;
}Node;

Node* create_linked_list()
{
	return NULL;
}

Node* insert_item(Node *node, unsigned char item, int priority) // Função de criação e inserção de nó na lista
{
	// ------------ Alocação/Definição do Nó -----------------

	Node *newnode = (Node*) malloc(sizeof(Node));
	newnode -> item = item;
	newnode -> priority = priority;
	newnode -> flag = 0;


	// --------------- Diferenciação do coringa ---------------

	if(item == '\\')
	{
		newnode -> flag = 1; // Marcação do caractere de escape
	}

	else if(item == '*')
	{
		newnode -> item = '\\'; // Caractere de escape para diferenciar do coringa
	}

	// ---------------- Setando o Nó --------------------------

	newnode -> next_node = node;
	newnode -> previous_node = NULL;

	if(newnode -> next_node != NULL)
	{
		newnode -> next_node -> previous_node = newnode;
	}

	newnode -> left = NULL;
	newnode -> right = NULL;

	return newnode;
}

Node* char_list(Node *list, int *frequency) // Função de criação da lista de frequências
{
	for(int i = 0; i < 256; i++)
	{
		if(frequency[i] != 0)
		{
			list = insert_item(list, i, frequency[i]);
		}
	}

	return list;
}

void bubble_sort(Node *first) // BubbleSort para ordenação da lista de acordo com as frequências
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


