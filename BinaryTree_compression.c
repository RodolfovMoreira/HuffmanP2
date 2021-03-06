/*BINARYTREE_COMPRESSION:

 Biblioteca da árvore usada na compressão, funções que criam e auxiliam na montagem da árvore de Huffman.

TYPEDEF STRUCT NODE :
Nó que será usado na biblioteca. está estruturado em:
Unsigned char item, int priority (ou frequência), int flag, struct Node *next_node, struct Node *previous_node, struct Node *left, struct Node *right. Nó que tem propriedades de árvore e lista.

-Funções-

NODE* SORT_TREE(NODE *ROOT) :
Durante a criação da árvore, depois que os dois primeiros elementos forem somados e reinseridos na lista, a função sort_tree(root) reordenará a lista de acordo com a prioridade.

NODE* MERGE_NODES(NODE *FIRST) :
Função que recebe a lista, retira os dois primeiros elementos, soma suas prioridades e cria um galho que terá como folha os mesmos. O galho é reinserido na lista.

INT TREE_SIZE(NODE *TREE, INT SIZE) :
Função que retorna o tamanho da árvore para criação do cabeçalho.

VOID PRINT_PRE_ORDER(NODE *TREE, FILE *PRINTING) :
Imprime o a árvore no cabeçalho do arquivo compactado.*/

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

Node* sort_tree(Node *root) // Reordena lista de acordo com prioridades
{
	while(root -> next_node != NULL && root -> priority > root -> next_node -> priority)
	{   // Enquanto não for o ultimo e frequência do atual for maior que o próximo
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
		root = root -> previous_node;
	}

	return root;
}

Node* merge_nodes(Node *first) // Cria Nó com soma das frequências dos dois primeiros da lista
{
	Node *root = (Node*) malloc(sizeof(Node));

	//--------- Criando galho ------------
	root -> item = '*';
	root -> priority = (first -> priority + first -> next_node -> priority); // Soma as frequências dos dois primeiros
	root -> flag = 0;
	root -> next_node = NULL;
	root -> previous_node = NULL;
	// ------------------------------------

	if(first -> next_node -> next_node != NULL)
	{
		root -> next_node = first -> next_node -> next_node; // Coloca o galho no início da lista
	}

	root -> left = first; // Left pega o menor
	root -> right = first -> next_node; // Right pega o próximo

	//---------- Setando o Nó ----------------
	root -> left -> next_node = NULL;
	root -> left -> previous_node = NULL;
	root -> right -> next_node = NULL;
	root -> right -> previous_node = NULL;
	//----------------------------------------

	return root;
}

int tree_size(Node *tree, int size) // Função que retorna o tamanho da árvore
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

Node* make_tree(Node *root) // Cria árvore de Huffman
{
	while(root -> next_node != NULL) // Enquanto a lista tiver mais que um elemento
	{
		root = merge_nodes(root);
		root = sort_tree(root);
	}

	return root;
}

void print_pre_order(Node *tree, FILE *printing) // Imprime a árvore no arquivo .huff
{
	if(tree != NULL)
	{
		fprintf(printing, "%c", tree->item); // Imprimindo cada caractere da árvore

		if(tree->flag) // Flag setada, imprime novamente para diferenciar na descompressão
		{
			fprintf(printing, "%c", tree->item);
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
