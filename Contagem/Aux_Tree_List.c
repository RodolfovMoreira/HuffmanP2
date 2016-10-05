#include "Aux_Tree_List.h"
#include <stdio.h>
#include <stdlib.h>

struct LinkedList{
	int item;
	LinkedList *next;
};

LinkedList* InitializeList(){
	return NULL;
}

LinkedList* CreateNode(LinkedList *first, int item){
	LinkedList *last = malloc(sizeof(LinkedList));

	last->item = item;
	last->next = first;

	return last;
}

int Peek(LinkedList *first){
	int numero;

	numero = first->item;

	return numero;
}

LinkedList* RemoveNode(LinkedList *first){
	LinkedList *auxiliar;

	auxiliar = first;

	first = first->next;

	free(auxiliar);

	return first;
}

int IsListEmpty(LinkedList *first){
	if(first == NULL){
		return 1;
	}else{
		return 0;
	}
}
