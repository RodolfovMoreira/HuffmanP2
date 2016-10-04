#include "Huff_Library.h"

typedef struct Hashtable{
	Character *table[257];
}Hashtable;

Hashtable* create_hashtable() // Função para criação da Hashtable que armazena o código de cada caractere
{
	Hashtable *ht = (Hashtable*) malloc(sizeof(Hashtable));

	for(int i = 0; i < 257; i++)
	{
		ht -> table[i] = NULL;
	}

	return ht;
}
