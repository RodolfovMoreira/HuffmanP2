/*HASHTABLE:

  Biblioteca utilizada para criação da hash table que armazenará os códigos de cara caractere.

TYPEDEF STRUCT HASHTABLE :
Estrutura da hash que utilizaremos. Terá o componente:
Character *table[257] (tipo de dado 'character', contido na biblioteca "PriorityQueue".

-Funções-

HASHTABLE* CREATE_HASHTABLE() :
Função de inicialização da hash, alocará espaço na memória e seta os 257 espaços para NULL. (hash terá um espaço a mais por uma peculiaridade do código)*/

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
