#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

typedef struct BinaryTree BinaryTree;

BinaryTree* InitializeTree();

BinaryTree* CreateLeaf(int item);

BinaryTree* InsertonTree(BinaryTree *root, int item);

BinaryTree* PopulateTree(); // DECLARE A 'BinaryTree' POINTER ON MAIN AND CALL THIS FUNCTION

int IsEmpty(BinaryTree *root);

void PrintInOrder(BinaryTree *root);

BinaryTree* SearchTree(BinaryTree *root, int item);

int SearchCount(BinaryTree *root, int item, int count); // COUNT = 1 ON THE FIRST CALL

int bingo(int intervalo);

void cleaner();

#endif /* BINARY_TREE_H_ */
