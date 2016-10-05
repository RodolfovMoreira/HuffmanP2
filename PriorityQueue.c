/*PRIORITYQUEUE

  Biblioteca de criação da fila.

TYPEDEF STRUCT CHARACTER:
Estrutura encontrada na biblioteca "PriorityQueue", contém: int code[30], int size.

TYPEDEF STRUCT HASHTABLE:
Ver biblioteca 'Hashtable' para mais informações.

TYPEDEF STRUCT Q_NODE:
Nó da fila, contém: Unsigned char item, int remain, struct Q_Node *next_qnode.

-Funções-

Q_NODE* ENQUEUE(Q_NODE* QUEUE, UNSIGNED CHAR ITEM):
Enfileira cada caractere do texto comprimido.

Q_NODE* TEXT_QUEUE(FILE *READING, Q_NODE *QUEUE, HASHTABLE *HT):
Reabre o arquivo original codifica cada caracte, quando um byte for preenchido adiciona na fila, no final adiciona o ultimo byte com o valor do lixo.

Q_NODE* COMPRESSED_QUEUE(FILE *COPYING, Q_NODE *D_QUEUE):
Armazena os caracteres no arquivo compactado numa fila.*/
#include "Huff_Library.h"

typedef struct Character{
	int code[30];
	int size;
}Character;

typedef struct Hashtable{
	Character *table[257];
}Hashtable;

typedef struct Q_Node{
	unsigned char item;
	int remain;
	struct Q_Node *next_qnode;
}Q_Node;

Q_Node* create_queue(){
	return NULL;
}

Q_Node* enqueue(Q_Node* queue, unsigned char item)
{
	Q_Node* newqnode = (Q_Node*) malloc(sizeof(Q_Node));
	newqnode -> item = item;
	newqnode -> remain = 0;

	if(queue == NULL) // Se a fila estiver vazia, adiciona na cabeça
	{
		return newqnode;
	}
	else
	{
		Q_Node* current = queue;

		while(current -> next_qnode != NULL) // Se não estiver, procura o último nó e adiciona nele
		{
			current = current -> next_qnode;
		}

		newqnode -> next_qnode = current -> next_qnode;
		current -> next_qnode = newqnode;
	}

	return queue;
}

Q_Node* text_queue(FILE *reading, Q_Node *queue, Hashtable *ht) // Enfileira texto codificado na ordem original
{
	unsigned char c = 0;
	int x, m, k = 0;

	// M = Auxiliar na obtenção dos bits no lugar correto (chars de escape)
	// K = Índice de controle do tamanho de C


	while((x = fgetc(reading))) // Abre o arquivo, lê e vai criando os unsg. e colocando na fila
	{
		if(x != EOF)
		{
			if(x == '*') // Se no texto houver '*', pega o código do contra barra sem flag (escape do '*')
			{
				m = '\\';
			}

			else if(x == '\\') // Se no texto houver '\', pega o código do contra barra com flag (escape do '\')
			{
				m = 256;
			}

			else
			{
				m = x; // Caso contrário pega a posição real na hash
			}

			for(int j = 0; j < ht->table[m] -> size; j++, k++) // Adiciona os bits de acordo com tamanho do código
			{
				if(k == 8) // Chegando ao último bit, imprime o unsg. e reenicia o preenchimento de outro unsg.
				{
					queue = enqueue(queue, c);
					c = 0;
					k = 0;
				}
				if(ht -> table[m] -> code[j]) // Caso o código conter '1', seta o unsigned na posição atual
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

	queue = enqueue(queue, c); // Enfileira o último caractere (não entrou no primeiro if pois o arquivo acabou)
	queue -> remain = 8-k; // Inteiro que guarda a quantidade de bits que foram preenchidas no último unsigned

	return queue;
}

Q_Node* compressed_queue(FILE *copying, Q_Node *D_Queue)
{
	int x;

	while(1)
	{
		x = fgetc(copying);

		if(feof(copying)) // Para se chegar ao fim do arquivo
		{
			break;
		}

		D_Queue = enqueue(D_Queue, x); // Enfileira cada unsigned numa fila
	}

	return D_Queue;
}
