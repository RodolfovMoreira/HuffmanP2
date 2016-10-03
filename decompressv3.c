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

BinaryTree* create_bt_node(unsigned char item, int flag)
{
	BinaryTree *newbt = (BinaryTree*) malloc(sizeof(BinaryTree));
	newbt -> item = item;
	newbt -> flag = flag;
	newbt -> left = NULL;
	newbt -> right = NULL;

	return newbt;
}

int index = 0; //INDICE DE CONTROLE DA POSICAO DA STRING DA ARVORE
//BACKSLASH - INDICE QUE MARCA A POSICAO DO CONTRA-BARRA REAL NA STRING

BinaryTree* remake_tree(BinaryTree *bt, unsigned char *string, int size, int backslash)
{
	if(index == size+1) //SE CHEGAR AO FIM DA LISTA DA ARVORE, RETORNA
	{
		return bt;
	}

	else
	{
		if(string[index] == '*') // SE ACHAR ASTERISCO, VAI PRA ESQUERDA E DEPOIS PARA A DIREITA
		{
			bt = create_bt_node(string[index], 0);
			index++;
			bt->left = remake_tree(bt->left, string, size, backslash);
			index++;
			bt->right = remake_tree(bt->right, string, size, backslash);
		}

		else //SE FOR UM CHAR QUALQUER, ADICIONA NA FOLHA E RETORNA
		{
			if(string[index] == '\\' && index == backslash) // VERIFICA SE ESTA NO CONTRA-BARRA REAL, SE FOR, ACIONA A FLAG
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
}

Q_Node* compressed_queue(FILE *copying, Q_Node *D_Queue)
{
	int x;

	while(1)
	{
		x = fgetc(copying);

		if(feof(copying)) //SE CHEGAR AO FIM DO ARQUIVO, PARA
		{
			break;
		}
		
		D_Queue = enqueue(D_Queue, x); //ENFILEIRA CADA UNSIGNED NUMA FILA
	}

	return D_Queue;
}

int sizeof_trash(Q_Node *queue)
{
	int k, count = 0;

	for(int i = 2, k = 0; i >= 0; i--, k++)
	{
		if(is_bit_set(queue->item, k))
		{
			count += pow(2, i); //CONVERTE PARA DECIMAL USANDO POTENCIAS DE DOIS
		}
	}

	return count;
}

int sizeof_tree(Q_Node *queue)
{
	int count, i, k = 3;

	for(count = 0, i = 12; i >= 0; k++, i--)
	{
		if(k == 8)
		{
			k = 0;
			queue = queue->next_qnode;
		}

		if(is_bit_set(queue->item, k))
		{
			count += pow(2, i); //CONVERTE PARA DECIMAL USANDO POTENCIAS DE DOIS
		}
	}

	return count;
}

void navigate_on_tree(FILE *newout, BinaryTree *root, Q_Node *queue, int size)
{
	BinaryTree *navigator = root;
	int k = 0;

	while(queue -> next_qnode != NULL) //ENQUANTO NAO CHEGAR NO ULTIMO NODE, ANDA NA ARVORE
	{
		if(k == 8) //SE CHEGAR AO FIM DE UM BYTE, ZERA O INDICE DE CONTROLE, E PULA DE NODE
		{
			k = 0;
			queue = queue -> next_qnode;
		}
		
		if(is_bit_set(queue -> item, k)) //SE FOR 1, VAI PRA DIREITA
		{
			navigator = navigator -> right;
		}
		
		else // SE FOR 0, VAI PRA ESQUERDA
		{
			navigator = navigator -> left;
		}
		
		if(navigator -> item != '*') // SE ACHAR UM CHAR, VERIFICA FLAG E IMPRIME
		{
			if(navigator -> item == '\\' && navigator -> flag == 0)
			{
				fprintf(newout, "*");
			}
			
			else
			{
				fprintf(newout, "%c", navigator -> item);
			}
			
			navigator = root; // VOLTA PARA RAIZ
		}
		
		k++; // AUMENTA INDICE DE BIT
	}

	while(7 - k >= size) // ULTIMO UNSIGNED, CONSIDERA TAMANHO DO LIXO. FAZ O MESMO PROCESSO QUE O LOOP ANTERIOR
	{
		if(is_bit_set(queue -> item, k))
		{
			navigator = navigator -> right;
		}
		
		else
		{
			navigator = navigator -> left;
		}
		
		if(navigator -> item != '*')
		{
			if(navigator -> item == '\\' && navigator -> flag == 0)
			{
				fprintf(newout, "*");
			}
			
			else
			{
				fprintf(newout, "%c", navigator -> item);
			}
			
			navigator = root;
		}
		
		k++;
	}
}

void decompress()
{
	//PEGA ARQUIVO COMPRESSO E MANDA PRA UMA FILA DE UNSIGNEDS

	FILE *compressed;
	compressed = fopen("compressed_file.huff", "r");

	Q_Node *D_Queue = create_queue();

	D_Queue = compressed_queue(compressed, D_Queue);

	// CONVERTER P/ DECIMAL OS 2 PRIMEIROS UNSIGNEDS

	Q_Node *current = D_Queue;

	int trash_size = sizeof_trash(current);
	int tree_size = sizeof_tree(current);

	// SETA CURRENT PARA O INICIO DA ARVORE

	for(int i = 0; i < 2; i++)
	{
		current = current->next_qnode;
	}

	// FAZER UMA STRING COM A ESTRUTURA DA ÁRVORE

	unsigned char insert_on_tree[tree_size];
	int backslash;
	
	for(int j = 0; j < tree_size; j++)
	{
		insert_on_tree[j] = current->item;

		if(current->item == '\\' && current->next_qnode != NULL) //SE FOR CONTRA-BARRA, VERIFICA SE PROXIMO NODE EXISTE
		{
			if(current->next_qnode->item == '\\') // SE EXISTIR, VERIFICA SE E CONTRA-BARRA. SE FOR, GUARDA A POSICAO DO CONTRA-BARRA REAL
			{
				backslash = j;
				current = current->next_qnode; // PULA UMA CASA A MAIS PARA EVITAR LER O PROXIMO CONTRA-BARRA NOVAMENTE
			}
		}

		current = current->next_qnode;
	}
	
	// MONTAR ÁRVORE ATÉ O TAM DA ÁRVORE ENCONTRADO //

	BinaryTree *root = create_empty_tree();
	root = remake_tree(root, insert_on_tree, tree_size, backslash);

	// NAVEGA NA ÁRVORE E IMPRIME NO ARQUIVO DE SAIDA OS CHARS CORRESPONDENTES A CODIFICACAO

	FILE *newout;
	newout = fopen("decompressed_file.txt", "w");

	navigate_on_tree(newout, root, current, trash_size);

	fclose(newout);
}

int main()
{
	decompress(); //FUNCAO DE DESCOMPRESSAO
	
	return 0;
}