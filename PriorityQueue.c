#include "HuffmanLibrary.h"

typedef struct Character{
	unsigned char bits;
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


