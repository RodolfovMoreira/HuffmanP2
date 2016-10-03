#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Character{
	int code[30];
	int size;
}Character;

typedef struct Hashtable{
	Character *table[257];
}Hashtable;

int set_bit(unsigned char bits, int position)
{
	unsigned char mask = 1 << (7 - position); // MUDA BIT NA POSIÇÃO MARCADA PARA 1
	return mask | bits;
}

Character* new_character(int *byte, int index) // ARMAZENA OS BITS EM CADA CASA DA HASH //
{
	Character *new_character = (Character*) malloc(sizeof(Character));

	for(int i = 0; i < index; i++) // RODA UM LOOP ATÉ A CASA ATUAL DO ARRAY BYTES //
	{
		new_character -> code[i] = byte[i]; // SE FOR 1, SETA 1 BIT NA POSIÇÃO, SE FOR 0, SETA 0 NA POSIÇÃO //
	}

	new_character -> size = index;

	return new_character;
}

Hashtable* create_hashtable() // FUNÇÃO PARA CRIAR HASHTABLE QUE ARMAZENA OS BITS DE CADA CARACTERE //
{
	Hashtable *ht = (Hashtable*) malloc(sizeof(Hashtable));

	for(int i = 0; i < 257; i++)
	{
		ht -> table[i] = NULL;
	}

	return ht;
}

Node* create_linked_list(){ //CRIAR LISTA ENCADEADA, APONTAR O PONTEIRO DO NÓ PARA NULO //
	return NULL;
}

Q_Node* create_queue(){
	return NULL;
}

Node* insert_item(Node *node, unsigned char item, int priority) // FUNÇÃO DE CRIAR E INSERIR NOVO NÓ A LISTA //
{
	Node *newnode = (Node*) malloc(sizeof(Node)); // ALOCAR ESPAÇO DE TAMANHO REFERENTE AO DADO NODE NA MEMÓRIA PARA O NOVO NÓ //
	newnode -> item = item; // SETAR O VALOR DO ITEM NA CAMADA ITEM DO NOVO NÓ //
	newnode -> priority = priority;
	newnode -> flag = 0;

	if(item == '\\')
	{
		newnode -> flag = 1; // MARCA O CHAR DE ESCAPE PARA DIFERENCIAR NA IMPRESSAO
	}

	else if(item == '*')
	{
		newnode -> item = '\\'; // CHAR DE ESCAPE PARA DIFERENCIAR DO ASTERISCO DA ÁRVORE
	}

	newnode -> next_node = node; // SETAR O PONTEIRO NEXTNODE DO NOVO NÓ PARA O NÓ ANTERIOR A ELE //
	newnode -> previous_node = NULL;

	if(newnode -> next_node != NULL)
	{
		newnode -> next_node -> previous_node = newnode; // SE O PRÓXIMO NÓ EXISTIR, FAZ SEU PREVIOUS APONTAR PARA A NOVA CABEÇA //
	}

	newnode -> left = NULL; // PREPARA ESTRUTURAS DA ÁRVORE //
	newnode -> right = NULL;
	
	return newnode;
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

Node* sort_tree(Node *root) // ROOT ANDA ENQUANTO NÃO CHEGAR AO FIM DA LISTA E ENQUANTO SUA PRIORIDADE FOR MAIOR QUE O PROXIMO
{
	while(root -> next_node != NULL && root -> priority > root -> next_node -> priority)
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
		root = root -> previous_node; // PROCURA A CABEÇA PARA RETORNAR
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

void print_pre_order(Node *tree, FILE *printing)
{
	if(tree != NULL)
	{
		fprintf(printing, "%c", tree->item); // IMPRIME CADA UNSIGNED DA ARVORE NO ARQUIVO DE SAIDA

		if(tree->flag) // SE A FLAG ESTIVER SETADA (ESCAPE DO CONTRA BARRA) IMPRIME NOVAMENTE PARA DIFERENCIAR NA DESCOMPRESSAO (MONTAGEM DA ÁRVORE)
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

void codify(Node *tree, Hashtable *ht, int *byte, int i)
{
	if(tree != NULL)
	{
		if(tree->item != '*')
		{
			if(tree->flag) // SE FOR O NODE QUE CONTEM O ESCAPE '\\' (FLAG SETADA) ADICIONA SEU CODIGO NO ESPAÇO EXTRA DA HASH
			{
				ht->table[256] = new_character(byte, i); // GUARDA OS BITS DO CARACTERE ATUAL ARMAZENADOS EM "BYTE" //
			}

			else
			{
				ht->table[tree->item] = new_character(byte, i); // GUARDA OS BITS DO CARACTERE ATUAL ARMAZENADOS EM "BYTE" //
			}
		}

		if(tree->left != NULL) // SE FOR PRA ESQUERDA, SETA 0 NO CODIGO E ANDA UMA CASA
		{
			byte[i] = 0;
			i++;
			codify(tree->left, ht, byte, i);
			i--;
		}

		if(tree->right != NULL) // SE FOR PRA DIREITA, SETA 1 NO CODIGO E ANDA UMA CASA
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

Node* char_list(Node *list, int *frequency)
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

Node* make_tree(Node *root) //ORDENAR NODES DA ARVORE ENQUANTO FAZ O MERGE
{
	while(root -> next_node != NULL) // SÓ CHAMA A FUNÇÃO SE HOUVER MAIS DE UM NODE SOBRANDO //
	{
		root = merge_nodes(root);
		root = sort_tree(root);
	}

	return root;
}

Q_Node* text_queue(FILE *reading, Q_Node *queue, Hashtable *ht) // FUNÇÃO QUE ENFILEIRA TEXTO JÁ CODIFICADO NA ORDEM ORIGINAL DE ENTRADA
{
	unsigned char c = 0;
	int x, m, k = 0;

	// OBS: M = AUXILIAR PARA PEGAR OS BITS DO LUGAR CORRETO (CASO DOS CHARS DE ESCAPE)
	// OBS: K = INDICE DE CONTROLE DO TAMANHO DE C //

	while((x = fgetc(reading))) //PEGA NOVAMENTE O ARQUIVO ORIGINAL E GUARDA OS BITS DE CADA LETRA, NA ORDEM, EM UMA FILA
	{
		if(x != EOF)
		{
			if(x == '*') // SE NO TEXTO TIVER ASTERISCO, PEGA O CODIGO DO CONTRA BARRA SEM FLAG (ESCAPE DO ASTERISCO)
			{
				m = '\\';
			}

			else if(x == '\\') // SE NO TEXTO TIVER CONTRA BARRA, PEGA O CÓDIGO DO CONTRA BARRA COM FLAG (ESCAPE DO CONTRA BARRA)
			{
				m = 256;
			}

			else
			{
				m = x; // CASO CONTRÁRIO, PEGA A POSIÇÃO REAL NA HASH
			}

			for(int j = 0; j < ht->table[m] -> size; j++, k++) // QUANDO ENCONTRAR, COPIA SEUS BITS, USANDO SEU TAMANHO PARA CONTROLAR //
			{
				if(k == 8) // QUANDO CHEGAR AO ULTIMO BIT, IMPRIME O CHAR E O ZERA, ZERANDO TAMBEM SEU INDICE DE CONTROLE //
				{
					queue = enqueue(queue, c);
					c = 0;
					k = 0;
				}

				if(ht -> table[m] -> code[j]) // VERIFICA BIT POR BIT ATÉ O TAMANHO, SE ESTIVER SETADO, SETA EM C //
				{
					c = set_bit(c, k);
				}
			}
		}

		else
		{
			break;
		}
	}

	queue = enqueue(queue, c); //ENFILEIRA ULTIMO CHAR QUE NÃO ENTROU NO PRIMEIRO IF POR CONTA DO ARQUIVO TER ACABADO
	queue -> remain = 8-k; // INTEIRO QUE GUARDA A QUANTIDADE DE BITS QUE  FORAM PREENCHIDAS NO ULTIMO UNSIGNED

	return queue;
}

void create_huff(FILE *writing, int *binary, Node *root, Q_Node *queue) // FUNCAO PARA ESCREVER TUDO O QUE FOI FEITO NO ARQUIVO .HUFF
{
	unsigned char c = 0;
	int k;

	// TAMANHOS DO LIXO E DA ARVORE

	for(int j = 0, k = 0; j < 16; j++, k++)
	{
		if(k == 8) // QUANDO COMPLETAR UM UNSIGNED PREENCHIDO, ESCREVE NO ARQUIVO
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

	fputc(c, writing); // ULTIMO CHAR PREENCHIDO

	// IMPRIMIR ARVORE NO ARQUIVO

	print_pre_order(root, writing);

	// ESCREVE NO ARQUIVO OS CHARS PRESENTES NA FILA, MANTENDO A ORDEM DO ARQUIVO ORIGINAL

	Q_Node *current = queue;

	while(current != NULL)
	{
		fputc(current -> item, writing);

		current = current -> next_qnode;
	}
}

void compress()
{
	//LER ARQUIVO

	FILE *input;
	int frequency[256] = {0};

	input = fopen("file.txt", "r");

	if(input == NULL)
	{
		printf("Error!\n");
		exit(0);
	}

	//CONTAR FREQUENCIA DE CADA CHAR EM UM ARRAY

	char_frequency(input, frequency);

	fclose(input);

	//ADICIONAR CHAR NUMA LISTA PARTINDO DO ARRAY ONDE NAO FOR NULO

	Node* list = create_linked_list();
	list = char_list(list, frequency);

	//ORDENAR LISTA EM ORDEM CRESCENTE

	bubble_sort(list);

	// MONTAGEM DA ÁRVORE

	Node *root = list;
	root = make_tree(root);

	//BUG DO CHAR UNICO (O CODIGO BUGA NA FUNCAO MERGE QUANDO TEMOS APENAS UM NODE. O PROCESSO ABAIXO CONTORNA ISSO)

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
	}

	//CODIFICAÇÃO

	int byte[30] = {0};
	int i = 0;

	Hashtable *ht = create_hashtable(); // CRIA HASH PARA GUARDAR BITS DE CADA CARACTERE EM ARRAYS
	
	codify(root, ht, byte, i); // CHAMA FUNÇÃO PARA CONTAR E SETAR OS BITS NUM ARRAY NA HASH

	//ORDEM DE IMPRESSAO DO TEXTO (CRIA FILA PARA GUARDAR A ORDEM DE IMPRESSAO DE ACORDO COM O TEXTO ORIGINAL)

	Q_Node *queue = create_queue();

	FILE *read;
	read = fopen("file.txt", "r");

	queue = text_queue(read, queue, ht);

	//TAMANHO DO LIXO

	int trash = queue -> remain;

	//PEGAR TAMANHO DA ARVORE

	int tree = 0;
	tree = tree_size(root, tree);

	// CONVERTER TAMANHOS DE LIXO E ARVORE PARA BINARIO

	int binary[16] = {0};
	decimal_to_binary(trash, binary, 2);
	decimal_to_binary(tree, binary, 15);

	// ESCREVER TUDO NO ARQUIVO .HUFF

	FILE *output;
	output = fopen("compressed_file.huff", "w");

	create_huff(output, binary, root, queue);

	fclose(output); // FECHA ARQUIVO
}

int main()
{
	compress(); // FUNÇÃO DE COMPRESSÃO

	return 0;
}