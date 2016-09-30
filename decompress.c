#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node{
	unsigned char item;
	int priority;
	int flag;
	struct Node *next_node;
	struct Node *previous_node;
	struct Node *left;
	struct Node *right;
}Node;


typedef struct BinaryTree{
	unsigned char item;
	int flag;
	struct BinaryTree *left;
	struct BinaryTree *right;
}BinaryTree;

typedef struct Q_Node{
	unsigned char item;
	int remain;
	struct Q_Node *next_qnode;
}Q_Node;

int is_bit_set(unsigned char bits, int position)
{
	unsigned char mask = 1 << (7 - position); // VERIFICA SE O BIT NA POSIÇÃO MARCADA ESTÁ EM 1
	return mask & bits;
}

int set_bit(unsigned char bits, int position)
{
	unsigned char mask = 1 << (7 - position); // MUDA BIT NA POSIÇÃO MARCADA PARA 1
	return mask | bits;
}

BinaryTree* create_empty_tree(){
	return NULL;
}

Node* create_linked_list(){
	return NULL;
}

Q_Node* create_queue(){
	return NULL;
}

Q_Node* enqueue(Q_Node* queue, unsigned char item)
{
	Q_Node* newqnode = (Q_Node*) malloc(sizeof(Q_Node));
	newqnode -> item = item;
	newqnode -> remain = 0;

	if(queue == NULL) //SE A FILA ESTIVER VAZIA, ADICIONA NA CABEÇA
	{
		return newqnode;
	}

	else
	{
		Q_Node* current = queue;

		while(current -> next_qnode != NULL) //SE NAO ESTIVER, PROCURA O ULTIMO NODE E ADICIONA NELE
		{
			current = current -> next_qnode;
		}

		newqnode -> next_qnode = current -> next_qnode;
		current -> next_qnode = newqnode;
	}

	return queue;
}

Node* insert_Tree_list(Node *Tree_List, Q_Node *current)
{
	Node *newnode = (Node*) malloc(sizeof(Node)); // ALOCAR ESPAÇO DE TAMANHO REFERENTE AO DADO NODE NA MEMÓRIA PARA O NOVO NÓ //
	newnode -> item = current -> item; 
	newnode -> priority = 0;
	newnode -> flag = 0;
	if(current -> item == '\\'){
		if(current -> next_qnode != NULL){
			if(current -> next_qnode -> item == '\\'){
				newnode -> flag = 1;
				current = current -> next_qnode;
			}
		}
	}

	if(Tree_List == NULL) 
	{
		return newnode;
	}

	else
	{
		Node* aux = Tree_List;

		while(aux -> next_node != NULL) //SE NAO ESTIVER, PROCURA O ULTIMO NODE E ADICIONA NELE
		{
			aux = aux -> next_node;
		}

		newnode -> next_node = aux -> next_node;
		aux -> next_node = newnode;
	}

	return Tree_List;
}

BinaryTree* create_Node_Bt(unsigned char item)
{
	BinaryTree *newbt = (BinaryTree*) malloc(sizeof(BinaryTree));
	newbt -> item = item;
	newbt -> flag = 0;
	newbt -> left = NULL;
	newbt -> right = NULL;

	return newbt;
}

int index = 0;

BinaryTree* Make_Dtree(BinaryTree *bt, unsigned char *string, int size)
{
	if(index == size){
		return bt;
	}

	else
	{
		if(string[index] == '*')
		{
			bt = create_Node_Bt(string[index]);
			index++;
			bt->left = Make_Dtree(bt->left, string, size);
			index++;
			bt->right = Make_Dtree(bt->right, string, size);
		}

		else
		{
			bt = create_Node_Bt(string[index]);
			return bt;
		}
	}

	return bt;
}

void print_pre_order(BinaryTree *tree)
{
	if(tree != NULL)
	{
		printf("%c\n", tree->item); // IMPRIME CADA UNSIGNED DA ARVORE NO ARQUIVO DE SAIDA

		if(tree->flag) // SE A FLAG ESTIVER SETADA (ESCAPE DO CONTRA BARRA) IMPRIME NOVAMENTE PARA DIFERENCIAR NA DESCOMPRESSAO (MONTAGEM DA ÁRVORE)
		{
			printf("%c\n", tree->item);
		}

		if(tree->left != NULL)
		{
			printf("esquerda\n");
			print_pre_order(tree->left);
		}

		if(tree->right != NULL)
		{
			printf("direita\n");
			print_pre_order(tree->right);
		}
	}

	printf("voltei\n");
}

int main(){
	
	FILE *compressed;
	Q_Node *D_Queue = create_queue();
	int size_trash;
	int size_tree;
	int x;
	compressed = fopen("compressed_file.huff", "r");

	while((x = fgetc(compressed))) 
	{
		if(x != EOF)
		{
			D_Queue = enqueue(D_Queue, x);
		}
		else{
			break;
		}
	}
	Q_Node *current = D_Queue;
	FILE *newout;
	newout = fopen("newout.txt", "w");
	while(current != NULL){
		fprintf(newout, "%c", current -> item);
		current = current->next_qnode;
	}

	printf("sai\n");
	int i, k, count = 0;
	// CONVERTER P/ DECIMAL OS 2 PRIMEIROS UNSIGNEDS //
	current = D_Queue;

	for(i = 2, k = 0; i >= 0; i--, k++)
	{
		if(is_bit_set(current->item, k))
		{
			count += pow(2, i);
		}
	}

	int Size_Trash = count; // TAM DO LIXO //
	// printf("lixo: %d\nk: %d\n", count, k);  TAM DO LIXO //

	for(count = 0, i = 12; i >= 0; k++, i--){
		if(k == 8)
		{
			k = 0;
			current = current->next_qnode;
		}
		if(is_bit_set(current->item, k))
		{
			//printf("%u\n", current->item);
			count += pow(2, i);
		}
	}

	printf("arvore: %d\n", count); // TAM DA ARVORE //
	int Size_Dtree = count;

	// FAZER UMA LISTA COM A ESTRUTURA DA ÁRVORE //
	unsigned char to_insert_tree[Size_Dtree];
	int j;
	for(j = 0; j < Size_Dtree; j++)
	{
		current = current->next_qnode;
		to_insert_tree[j] = current->item;
		printf("%c", to_insert_tree[j]);
	}
	printf("\n");
	// MONTAR ÁRVORE ATÉ O TAM DA ÁRVORE ENCONTRADO //
	BinaryTree *root = create_empty_tree();
	root = Make_Dtree(root, to_insert_tree, Size_Dtree);
	print_pre_order(root);
	// ARVORE IS READY

	current = current -> next_qnode;
	printf("atual:%c\n", current->item);
	BinaryTree *navigator = root;
	k = 0;

	while(current -> next_qnode != NULL){
		if(k == 8){
			k = 0;
			current = current->next_qnode;
		}
		if(is_bit_set(current->item, k)){
			navigator = navigator -> right;
		}
		else navigator = navigator -> left;
		if(navigator -> item != '*')
		{
			if(navigator -> item == '\\' && navigator -> flag == 0)
			{
				printf("*");
			}
			else{
				printf("%c", navigator -> item);
			}
			navigator = root;
		}
		k++;		
	}
	printf("\n");

	return 0;
}