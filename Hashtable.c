#include "HuffmanLibrary.h"

typedef struct Hashtable{
	Character *table[257];
}Hashtable;

Hashtable* create_hashtable() // Cria Hashtable que armazena o código de cada caractere
{
	Hashtable *ht = (Hashtable*) malloc(sizeof(Hashtable));

	for(int i = 0; i < 257; i++)
	{
		ht -> table[i] = NULL;
	}

	return ht;
}
