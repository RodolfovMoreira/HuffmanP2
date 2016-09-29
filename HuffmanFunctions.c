#include "HuffmanLibrary.h"

typedef struct Q_Node{
	unsigned char item;
	int remain;
	struct Q_Node *next_qnode;
}Q_Node;

typedef struct Character{
	unsigned char bits;
	int size;
}Character;

int is_bit_set(unsigned char bits, int position)
{
	unsigned char mask = 1 << (7 - position); // Verifica se o bit na posição está setado
	return mask & bits;
}

int set_bit(unsigned char bits, int position)
{
	unsigned char mask = 1 << (7 - position); // Seta o bit da posição marcada
	return mask | bits;
}

Q_Node* create_queue(){
	return NULL;
}

Character* new_character(int *bytes, int index) // Armazena os bits na hash
{
	Character *new_character = (Character*) malloc(sizeof(Character));

	new_character -> bits = 0; // Seta posição para 0

	for(int i = 0; i < index; i++) // RODA UM LOOP ATÉ A CASA ATUAL DO ARRAY BYTES //
	{
		if(bytes[i] == 1) // SE FOR 1, SETA O BIT //
		{
			new_character -> bits = set_bit(new_character -> bits, i);
		}
	}

	new_character -> size = index;

	return new_character;
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

				if(is_bit_set(ht -> table[m] -> bits, j)) // VERIFICA BIT POR BIT ATÉ O TAMANHO, SE ESTIVER SETADO, SETA EM C //
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
	queue -> remain = k; // INTEIRO QUE GUARDA A QUANTIDADE DE BITS QUE  FORAM PREENCHIDAS NO ULTIMO UNSIGNED

	return queue;
}

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

		if(tree->left != NULL)
		{
			byte[i] = 0;
			i++;
			codify(tree->left, ht, byte, i);
			i--;
		}

		if(tree->right != NULL)
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

void create_huff(FILE *writing, int *binary, Node *root, Q_Node *queue) // FUNCAO PARA ESCREVER TUDO O QUE FOI FEITO NO ARQUIVO .HUFF
{
	unsigned char c = 0;
	int k;

	// TAMANHOS

	for(int j = 0, k = 0; j < 16; j++, k++)
	{
		if(k == 8)
		{
			fprintf(writing, "%u", c);
			c = 0;
			k = 0;
		}

		if(binary[j])
		{
			c = set_bit(c, k);
		}
	}

	fprintf(writing, "%u", c); // ULTIMO CHAR PREENCHIDO

	// IMPRIMIR ARVORE NO ARQUIVO

	print_pre_order(root, writing);

	// ESCREVER NO ARQUIVO OS CHARS PRESENTES NA FILA, MANTENDO A ORDEM DO ARQUIVO ORIGINAL

	Q_Node *current = queue;

	while(current != NULL)
	{
		fprintf(writing, "%u", current -> item);

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

	//CODIFICAÇÃO

	int byte[8] = {0};
	int i = 0;

	Hashtable *ht = create_hashtable(); // CRIA HASH PARA GUARDAR BITS DE CADA CARACTERE //

	codify(root, ht, byte, i); // CHAMA FUNÇÃO PARA CONTAR E SETAR OS BITS //

	//ORDEM DE IMPRESSAO DO TEXTO

	Q_Node *queue = create_queue();

	FILE *read;
	read = fopen("file.txt", "r");

	queue = text_queue(read, queue, ht);

	//TAMANHO DO LIXO

	int trash = (8 - queue -> remain);

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

	fclose(output); // FECHA ARQUIVO //
}
