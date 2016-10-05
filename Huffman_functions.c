/* 5 - HUFFMAN_FUNCTIONS:

  Biblioteca que reúne as funções necessárias para compressão e descompressão, utilizando de todas as outras bibliotecas auxiliares.

TYPEDEF STRUCT CHARACTER : Ver descrição na biblioteca "PriorityQueue". Estrutura encontrada na biblioteca "PriorityQueue", contém: int code[30], int size.

TYPEDEF STRUCT HASHTABLE :  Ver descrição na biblioteca "Hashtable".

TYPEDEF STRUCT NODE : Ver descrição na biblioteca "BinaryTree_compression".

TYPEDEF STRUCT Q_NODE : Ver descrição na biblioteca "PriorityQueue".

TYPEDEF STRUCT BINARYTREE : Ver descrição na biblioteca "BinaryTree_decompression".

-Funções-

INT SET_BIT(UNSIGNED CHAR BITS, INT POSITION) :
Função utilizada para setar os bits da posição 'position' dada.

INT IS_BIT_SET(UNSIGNED CHAR BITS, INT POSITION) :
Função que verifica se o bit da posição 'position' está setado.

VOID CHAR_FREQUENCY(FILE *COUNTING, INT *FREQUENCY) :
Função que pega as frequências de cada caractere e armazena num array.

CHARACTER* NEW_CHARACTER(INT *BYTE, INT INDEX) :
Função que transfere o código do caractere obtido pela função 'codify' para a hashtable.

VOID CODIFY(NODE *TREE, HASHTABLE *HT, INT BYTE, INT I) :
Função que pega a codificação de cada caractere.
Utiliza-se de recursão e tem semelhança com o algorítimo de printpreorder para obtenção dos códigos.
Quando a função encontra um nó, ela armazena o código até agora obtido.

VOID DECIMAL_TO_BINARY(INT DECIMAL, INT *BINARY, INT INDEX) :
Transforma um número decimal em binário. (utilizada para criação do cabeçalho)

VOID CREATE_HUFF(FILE *WRITING, INT *BINARY, NODE *ROOT, Q_NODE *QUEUE):
Função que faz o cabeçalho e imprime a árvore no arquivo '.huff'

NODE* UNIQUE_CHAR(NODE *ROOT) :
Função que somente é chamada quando o arquivo a ser compactado contém somente um caractere.

VOID COMPRESS():
Função que organiza e chama todas as outras necessárias para criação do arquivo compactado.

INT POWN(INT NUMBER, INT I):
Função de calcula potências.

INT SIZEOF_TRASH(Q_NODE *QUEUE):
Função que calcula o tamanho do lixo.

INT SIZEOF_TREE(Q_NODE *QUEUE):
Função que calcula o tamanho do lixo.

VOID NAVIGATE_ON_TREE(FILE *NEWOUT, BINARYTREE *ROOT, Q_NODE *QUEUE, INT SIZE):
Função que recebe uma fila de unsigneds e vai descompactando um por um.

VOID DECOMPRESS():
Função que organiza e chama todas as outras necessárias para o arquivo ser descompactado.*/

#include "Huff_Library.h"


// --------- ESTRUTURAS -----------

typedef struct Character{
	int code[30];
	int size;
}Character;

typedef struct Hashtable{
	Character *table[257];
}Hashtable;

typedef struct Node{
	unsigned char item;
	int priority;
	int flag;
	struct Node *next_node;
	struct Node *previous_node;
	struct Node *left;
	struct Node *right;
}Node;

typedef struct Q_Node{
	unsigned char item;
	int remain;
	struct Q_Node *next_qnode;
}Q_Node;

typedef struct BinaryTree{
	unsigned char item;
	int flag;
	struct BinaryTree *left;
	struct BinaryTree *right;
}BinaryTree;


//------ BITSHIFT OPERATORS ------

int set_bit(unsigned char bits, int position)
{
	unsigned char mask = 1 << (7 - position); // Muda bit na posição marcada para '1'
	return mask | bits;
}

int is_bit_set(unsigned char bits, int position)
{
	unsigned char mask = 1 << (7 - position); // Verifica se o bit na posição marcada é o '1'
	return mask & bits;
}

// ------------  HUFFMAN FUNCTIONS - COMPRESSION -----------------

void char_frequency(FILE *counting, int *frequency)
{
	int x;

	while((x = fgetc(counting)))
	{
		if(x != EOF)
		{
			frequency[x]++;
		}

		else
		{
			break;
		}
	}
}

Character* new_character(int *byte, int index) // Armazena o código em cada casa da Hash
{
	Character *new_character = (Character*) malloc(sizeof(Character));

	for(int i = 0; i < index; i++) // Itera até onde o byte está preenchido
	{
		new_character -> code[i] = byte[i]; // Se for 1, code[i] = 1, caso contrário, code[i] = 0
	}

	new_character -> size = index;

	return new_character;
}

void codify(Node *tree, Hashtable *ht, int *byte, int i) // Criação dos códigos dos caracteres
{
	if(tree != NULL)
	{
		if(tree->item != '*')
		{
			if(tree->flag) // Se for o node do escape '\\' (flag set) adiciona seu código no espaço extra da hash
			{
				ht->table[256] = new_character(byte, i); // Guarda os bits do caractere atual
			}

			else
			{
				ht->table[tree->item] = new_character(byte, i); // Guarda os bits do caractere atual
			}
		}
		if(tree->left != NULL) // Se for para esquerda, seta 0 e anda uma casa
		{
			byte[i] = 0;
			i++;
			codify(tree->left, ht, byte, i);
			i--;
		}
		if(tree->right != NULL) // Se for para direita, seta 1 e anda uma casa
		{
			byte[i] = 1;
			i++;
			codify(tree->right, ht, byte, i);
			i--;
		}
	}
}

void decimal_to_binary(int decimal, int *binary, int index)
{
	if(decimal/2 == 0)
	{
		binary[index] = decimal%2;
		return;
	}

	else
	{
		binary[index] = decimal%2;
		decimal/=2;
		index--;
		return decimal_to_binary(decimal, binary, index);
	}
}

void create_huff(FILE *writing, int *binary, Node *root, Q_Node *queue) // Cria arquivo .huff
{
	unsigned char c = 0;
	//int k;

	// Tamanho de lixo/árvore (obtido na codify)

	for(int j = 0, k = 0; j < 16; j++, k++)
	{
		if(k == 8) // Completar um byte escreve no arquivo
		{
			fputc(c, writing);
			c = 0;
			k = 0;
		}

		if(binary[j])
		{
			c = set_bit(c, k);
		}
	}

	fputc(c, writing); // Último unsigned preenchido

	// Imprimir árvore no arquivo

	print_pre_order(root, writing);

	// Escreve no arquivo os chars da fila, mantendo a ordem original

	Q_Node *current = queue;

	while(current != NULL)
	{
		fputc(current -> item, writing);

		current = current -> next_qnode;
	}
}

Node* unique_char(Node *root) // Resolve problema do arquivo com somente 1 caractere
{
	if(root -> item != '*')
		{
		Node *aux = (Node*) malloc(sizeof(Node));  // CRIA RAIZ PARA AGRUPAR DOIS NODES //
		aux -> item = '*'; // CHAR DE REPRESENTAÇÃO //
		aux -> priority = root -> priority; // SOMA AS PRIORIDADES DOS DOIS MENORES //
		aux -> flag = 0;
		aux -> next_node = NULL;
		aux -> previous_node = NULL;
		aux -> left = root; // LEFT PEGA O MENOR //
		aux -> right = NULL;
		root = aux;
		return root;
	}else{
		return root;
	}
}

void compress()
{
	// Ler arquivo

	FILE *input;
	int frequency[256] = {0};

	input = fopen("file.txt", "r");

	if(input == NULL)
	{
		printf("Error!\n");
		exit(0);
	}

	// Contar frequência

	char_frequency(input, frequency);

	fclose(input);

	// Criar lista com frequências

	Node* list = create_linked_list();
	list = char_list(list, frequency);

	// Ordenar lista em ordem crescente

	bubble_sort(list);

	// Montagem da árvore

	Node *root = list;
	root = make_tree(root);

	// Função abaixo contorna problema quando arquivo a ser compactado contém somente um caractere

	unique_char(root);

	//Criação da codificação

	int byte[30] = {0};
	int i = 0;

	Hashtable *ht = create_hashtable(); // Hash de armazenamento dos códigos

	codify(root, ht, byte, i); // Função para coleta e armazenagem dos códigos

	// Fila para impressão de acordo com o texto original
	Q_Node *queue = create_queue();

	FILE *read;
	read = fopen("file.txt", "r");

	queue = text_queue(read, queue, ht);

	// Obtenção do tamanho do lixo

	int trash = queue -> remain;

	// Obtenção do tamanho da árvore

	int tree = 0;
	tree = tree_size(root, tree);

	// Conversão do tamanho do lixo e da árvore para binário

	int binary[16] = {0};
	decimal_to_binary(trash, binary, 2);
	decimal_to_binary(tree, binary, 15);

	// Criação do .huff

	FILE *output;
	output = fopen("compressed_file.huff", "w");

	create_huff(output, binary, root, queue);

	fclose(output);
}

// --------- DECOMPRESSION ----------

int pown(int number, int i)
{
	if(i==0){
		return 1;
	}
	int p = i;
	int aux = number;

	for(i = 1; i < p; i++){
		number = number*aux;
	}
	return number;
}

int sizeof_trash(Q_Node *queue)
{
	int k, count = 0;

	for(int i = 2, k = 0; i >= 0; i--, k++)
	{
		if(is_bit_set(queue->item, k))
		{
			count += pown(2, i); // Converte para decimal
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
			count += pown(2, i); //Converte para decimal
		}
	}

	return count;
}

void navigate_on_tree(FILE *newout, BinaryTree *root, Q_Node *queue, int size)
{
	BinaryTree *navigator = root;
	int k = 0;

	while(queue -> next_qnode != NULL) //Enquanto não chegar ao último Nó, anda na árvore
	{
		if(k == 8) // Ao chegar no fim de um byte, zera o índice e pega o próximo
		{
			k = 0;
			queue = queue -> next_qnode;
		}

		if(is_bit_set(queue -> item, k)) // Caso for '1', vai para direita
		{
			navigator = navigator -> right;
		}

		else // Caso for 0, vai para a esquerda
		{
			navigator = navigator -> left;
		}

		if(navigator -> item != '*') // Se achar um caractere, verifica flag e imprime
		{
			if(navigator -> item == '\\' && navigator -> flag == 0)
			{
				fprintf(newout, "*");
			}

			else
			{
				fprintf(newout, "%c", navigator -> item);
			}

			navigator = root; // Volta para raiz
		}

		k++; // Aumenta índice do bit
	}

	while(7 - k >= size) // Último unsigned (Considerando o tamanho do lixo)
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

int indexer = 0;

BinaryTree* remake_tree(BinaryTree *bt, unsigned char *string, int size, int backslash)
{
	if(indexer == size+1) // Retorna se chegar ao fim da lista da árvore
	{
		return bt;
	}

	else
	{
		if(string[indexer] == '*') // Se achar '*', vai para esquerda e depois para direita
		{
			bt = create_bt_node(string[indexer], 0);
			indexer++;
			bt->left = remake_tree(bt->left, string, size, backslash);
			indexer++;
			bt->right = remake_tree(bt->right, string, size, backslash);
		}

		else // Caso um char qualquer, cria folha e retorna
		{
			if(string[indexer] == '\\' && indexer == backslash) // Verifica se está no '\' real, se for, aciona a flag
			{
				bt = create_bt_node(string[indexer], 1);
				return bt;
			}

			else
			{
				bt = create_bt_node(string[indexer], 0);
				return bt;
			}
		}
	}

	return bt;
}

void decompress()
{
	// Pega o arquivo compresso e envia para uma fila de unsigneds.

	FILE *compressed;
	compressed = fopen("compressed_file.huff", "r");

	Q_Node *D_Queue = create_queue();

	D_Queue = compressed_queue(compressed, D_Queue);

	// Converter para decimal os dois primeiros bytes

	Q_Node *current = D_Queue;

	int trash_size = sizeof_trash(current);
	int tree_size = sizeof_tree(current);

	// Seta current para início da árvore

	for(int i = 0; i < 2; i++)
	{
		current = current->next_qnode;
	}

	// Criação de uma string com a estrutura da árvore

	unsigned char insert_on_tree[tree_size];
	int backslash;

	for(int j = 0; j < tree_size; j++)
	{
		insert_on_tree[j] = current->item;

		if(current->item == '\\' && current->next_qnode != NULL) // Caso for '\' verifica se o próximo node existe
		{
			if(current->next_qnode->item == '\\') // Se existir, verifica se é '\', caso for, guarda sua posição
			{
				backslash = j;
				current = current->next_qnode; // Pula uma casa para evitar ler o próximo '\'
			}
		}

		current = current->next_qnode;
	}

	// Montar árvore até atingir o tamanho da mesma

	BinaryTree *root = create_empty_tree();

	root = remake_tree(root, insert_on_tree, tree_size, backslash);

	// Navega na árvore imprimindo a cada chegada em folha

	FILE *newout;
	newout = fopen("decompressed_file.txt", "w");

	navigate_on_tree(newout, root, current, trash_size);

	fclose(newout);
}

