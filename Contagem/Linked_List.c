#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node{
	int item;
	struct Node *nextNode;
}Node;

Node* createLinkedList(){ //CRIAR LISTA ENCADEADA, APONTAR O PONTEIRO DO NÓ PARA NULO //
	return NULL;
}
/* INSERIR NO INICIO
Node* insertItem(Node *first, int item){ // FUNÇÃO DE CRIAR E INSERIR NOVO NÓ A LISTA //
	Node *newnode = (Node*) malloc(sizeof(Node)); // ALOCAR ESPAÇO DE TAMANHO REFERENTE AO DADO NODE NA MEMÓRIA PARA O NOVO NÓ //
	newnode -> item = item; // SETAR O VALOR DO ITEM NA CAMADA ITEM DO NOVO NÓ //
	newnode -> nextNode = first; // SETAR O PONTEIRO NEXTNODE DO NOVO NÓ PARA O NÓ ANTERIOR A ELE //
	return newnode;
}*/

// INSERIR NO FINAL
Node* InsertItem(Node *first, int item){

	Node *aux;
	Node *newnode = (Node*) malloc(sizeof(Node));

	aux = first;

	newnode->item = item;
	newnode->nextNode = NULL;

	if(first == NULL){
		return newnode;
	}
	else{

		while(1){
			if(aux->nextNode == NULL){
				aux->nextNode = newnode;
				break;
			}
			aux = aux->nextNode;
		}
		aux = first;
		return aux;
	}
}
int search(Node *first, int item){
	int comparisons = 0;
	Node *p;
	for (p = first; p != NULL; p = p->nextNode, comparisons++) {
		if(p->item == item){
			return comparisons;
		}
	}
	return comparisons;
}

