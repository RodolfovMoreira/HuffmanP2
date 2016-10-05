#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Linked_List.h"
#include "Binary_Tree.h"

int main()
{
	int i, number, comparacoes, contagem;;
	FILE *fp;
	FILE *aux;
	BinaryTree *root;

	//------LISTA--------
	Node *list;//= (Node*) malloc(sizeof(Node));
	list = createLinkedList();

	cleaner();

	fp = fopen("linkedcomparisons.csv", "w");

	fprintf(fp, "Numero,comparações\n");

	for(i = 1; i < 10001; i++){
		list = InsertItem(list, i);
	}
	int sorted;
	for(i = 0; i < 1000; i++){
		sorted = bingo(10000);
		int x = search(list, sorted);
		fprintf(fp, "%d,%d\n", sorted, x);
	}


	//-------ARVORE--------

	cleaner();

	root = PopulateTree();

	aux = fopen("treecomparisons.csv", "w");

	fprintf(aux,"Numero,Comparações\n");

//	PrintInOrder(root);
//	printf("\nDone\n");
	//LEMBRE-SE QUE SE A COMPARAÇÃO RETORNAR '0' É PORQUE NÃO EXISTE TAL NUMERO NA ÁRVORE

	contagem = 1;

	while(contagem <= 1000){
		number = bingo(10000);
		//printf("%d,", number);
		comparacoes = SearchCount(root, number, 1);
		printf("%d,", comparacoes);
		if(comparacoes != 0){
			fprintf(aux,"%d,%d\n",number,comparacoes);
			contagem++;
		}

//		printf("numero: %d , comparacoes necessarias: %d\n", number, comparacoes);
	}


	return 0;
}
