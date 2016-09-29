#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	unsigned char item;
	int priority;
	struct Node *next_node;
	struct Node *previous_node;
	struct Node *left;
	struct Node *right;
}Node;

typedef struct Q_Node{
	unsigned char item;
	struct Q_Node *next_qnode;
}Q_Node;

typedef struct Character{
	unsigned char bits;
	int size;
}Character;

typedef struct Hashtable
{
	Character *table[256];
}Hashtable;

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

Character* new_character(int *bytes, int index) // ARMAZENA OS BITS EM CADA CASA DA HASH //
{
	Character *new_character = (Character*) malloc(sizeof(Character));
	new_character -> bits = 0; // SETA OS BITS DO CHAR EM ZERO //

	int i = 0;

	for(i = 0; i < index; i++) // RODA UM LOOP ATÉ A CASA ATUAL DO ARRAY BYTES //
	{
		if(bytes[i] == 1) // SE FOR 1, SETA O BIT //
		{
			new_character -> bits = set_bit(new_character -> bits, i);
		}
	}

	new_character -> size = index;

	return new_character;
}

Hashtable* create_hashtable() // FUNÇÃO PARA CRIAR HASHTABLE QUE ARMAZENA OS BITS DE CADA CARACTERE //
{
	Hashtable *ht = (Hashtable*) malloc(sizeof(Hashtable));

	int i;
	for(i = 0; i < 256; i++)
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

void print_linked_list(Node *first) // IMPRIMIR O CONTEUDO DA LISTA //
{
	if(first != NULL)
	{
		printf("%u %d\n", first -> item, first -> priority);
		print_linked_list(first -> next_node); // CHAMAR RECURSIVAMENTE A FUNÇÃO PRINT ENQUANDO P NÃO APONTAR PARA NULO //
	}
}

void bubble_sort(Node *first)
{
	char aux_item;
	int aux_priority;

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
				hold -> item = current -> item;
				hold -> priority = current -> priority;
				current -> item = aux_item;
				current -> priority = aux_priority;
			}
		}
	}
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

	root = sort_tree(root); // FUNÇÃO DE REORDENAÇÃO //

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
		fprintf(printing, "%u", tree->item); // IMPRIME CADA UNSIGNED DA ARVORE NO ARQUIVO DE SAIDA
		fprintf(printing, "\n");

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
			ht->table[tree->item] = new_character(byte, i); // GUARDA OS BITS DO CARACTERE ATUAL ARMAZENADOS EM "BYTE" //
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

int* decimal_to_binary(int decimal, int *binary, int index)
{
	if(decimal/2 == 0)
	{
		binary[index] = decimal%2;
		return binary;
	}

	else
	{
		binary[index] = decimal%2;
		decimal/=2;
		index--;
		return decimal_to_binary(decimal, binary, index);
	}
}

int main()
{
	//LER ARQUIVO

	FILE *input;
	int frequency[256] = {0};

	input = fopen("leitura.txt", "r");

	if(input == NULL)
	{
		printf("Error!\n");
		exit(0);
	}

	//CONTAR FREQUENCIA DE CADA CHAR EM UM ARRAY

	int x;
	unsigned char aux = '\\'; //CHAR DE ESCAPE PARA O ASTERISCO

	while((x = fgetc(input)))
	{
		if(x != EOF)
		{
			if(x == '*')
			{
				frequency[aux]++;
			}

			else if(x != 10)
			{
				frequency[x]++;
			}
		}

		else
		{
			break;
		}
	}

	fclose(input);

	//ADICIONAR CHAR NUMA LISTA PARTINDO DO ARRAY ONDE NAO FOR NULO

	Node* list = create_linked_list();

	for(int i = 0; i < 256; i++)
	{
		if(frequency[i] != 0)
		{
			list = insert_item(list, i, frequency[i]);
		}
	}

	//ORDENAR LISTA EM ORDEM CRESCENTE

	bubble_sort(list);

	Node *root = (list);

	//ORDENAR NODES DA ARVORE ENQUANTO FAZ O MERGE

	while(root -> next_node != NULL) // SÓ CHAMA A FUNÇÃO SE HOUVER MAIS DE UM NODE SOBRANDO //
	{
		root = merge_nodes(root);
	}

	//CODIFICAÇÃO

	int byte[8] = {0};
	int i = 0;

	Hashtable *ht = create_hashtable(); // CRIA HASH PARA GUARDAR BITS DE CADA CARACTERE //
	codify(root, ht, byte, i); // CHAMA FUNÇÃO PARA CONTAR E SETAR OS BITS //

	//ORDEM DE IMPRESSAO

	Q_Node *queue = create_queue();

	unsigned char c = 0;
	int k = 0;

	FILE *read;
	read = fopen("leitura.txt", "r");

	while((x = fgetc(read))) //PEGA NOVAMENTE O ARQUIVO ORIGINAL E GUARDA OS BITS DE CADA LETRA, NA ORDEM, EM UMA FILA
	{
		if(x != EOF && x != 10)
		{
			for(int j = 0; j < ht->table[x] -> size; j++, k++) // QUANDO ENCONTRAR, COPIA SEUS BITS, USANDO SEU TAMANHO PARA CONTROLAR //
			{
				if(k == 8) // QUANDO CHEGAR AO ULTIMO BIT, IMPRIME O CHAR E O ZERA, ZERANDO TAMBEM SEU INDICE DE CONTROLE //
				{
					queue = enqueue(queue, c);
					c = 0;
					k = 0;
				}

				if(is_bit_set(ht -> table[x] -> bits, j)) // VERIFICA BIT POR BIT ATÉ O TAMANHO, SE ESTIVER SETADO, SETA EM C //
				{
					c = set_bit(c, k);
				}

				// OBS: K = INDICE DE CONTROLE DO TAMANHO DE C //
			}
		}

		else
		{
			break;
		}
	}

	queue = enqueue(queue, c); //ENFILEIRA ULTIMO CHAR QUE NÃO ENTROU NO SEGUNDO IF POR CONTA DO ARQUIVO TER ACABADO

	//TAMANHO DO LIXO

	int trash = (8 - k);

	//PEGAR TAMANHO DA ARVORE

	int tree = 0;
	tree = tree_size(root, tree);

	// CONVERTER TAMANHOS DE LIXO E ARVORE PARA BINARIO

	int binary[16] = {0};

	decimal_to_binary(trash, binary, 2);
	decimal_to_binary(tree, binary, 15);

	// ESCREVER TUDO NO ARQUIVO .HUFF

	FILE *output;

	output = fopen("teste.txt", "w");

	c = 0;

	// TAMANHOS

	for(int j = 0, k = 0; j < 16; j++, k++)
	{
		if(k == 8)
		{
			fprintf(output, "%u", c);
			fprintf(output, "\n");
			c = 0;
			k = 0;
		}

		if(binary[j])
		{
			c = set_bit(c, k);
		}
	}

	fprintf(output, "%u", c); // ULTIMO CHAR PREENCHIDO
	fprintf(output, "\n");

	// IMPRIMIR ARVORE NO ARQUIVO

	print_pre_order(root, output);

	// ESCREVER NO ARQUIVO OS CHARS PRESENTES NA FILA, MANTENDO A ORDEM DO ARQUIVO ORIGINAL

	Q_Node *current = queue;

	while(current != NULL)
	{
		fprintf(output, "%u", current -> item);
		fprintf(output, "\n");

		current = current -> next_qnode;
	}

	fclose(output); // FECHA ARQUIVO //

	//********OBS: VER "BARRA-BARRA"

	return 0;
}
