/*
 * BinaryTree.c
 *
 *  Created on: 9 de set de 2016
 *      Author: rodol
 */

#include "Binary_Tree.h"
#include "Aux_Tree_List.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-------------- Random Functions -----------------------

int bingo(int intervalo)
{

	int x;
	x = rand() % intervalo;
	return x;
}

void cleaner()
{
	srand((unsigned)time(NULL));
}

// ----------------- Estrutura Árvore -------------------

struct BinaryTree {
	int item;
	BinaryTree *left;
	BinaryTree *right;
};

BinaryTree* InitializeTree()
{
	return NULL;
}

BinaryTree* CreateLeaf(int item)
{
	BinaryTree *bt = malloc(sizeof(BinaryTree));

	bt->item = item;
	bt->left = NULL;
	bt->right = NULL;

	return bt;
}

BinaryTree* InsertonTree(BinaryTree *root, int item)
{
	if(root == NULL){
		root = CreateLeaf(item);
	} else if(root->item == item){
		return root;
	} else if(root->item > item){
		root->left = InsertonTree(root->left, item);
	} else{
		root->right = InsertonTree(root->right, item);
	}

	return root;
}

BinaryTree* PopulateTree()
{
	BinaryTree *root = InitializeTree();

	int i, sorted;

	cleaner();

	root = InsertonTree(root, 5000);


	for(i = 0; i < 30000; i++){
		sorted = bingo(10000);

		root = InsertonTree(root, sorted);
	}

	return root;
}

int IsEmpty(BinaryTree *root)
{
	if(root == NULL){
		return 1;
	}else{
		return 0;
	}
}

void PrintInOrder(BinaryTree *root)
{
	if(!IsEmpty(root)){
		PrintInOrder(root->left);
		printf("(%d)", root->item);
		PrintInOrder(root->right);
	}
}

int SearchCount(BinaryTree *root, int item, int count) // RETORNA '0' SE NÃO ENCONTRAR, COUNT COMEÇA 1
{
	while(1){
		if(root == NULL){
			return 0;
		} else if(root->item == item){
			return count;
		} else if(root->item > item){
			count++;
			return SearchCount(root->left, item, count);
		} else{
			count++;
			return SearchCount(root->right, item, count);
		}
	}
}
