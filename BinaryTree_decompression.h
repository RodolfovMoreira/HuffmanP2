#ifndef BINARYTREE_DECOMPRESSION_H_
#define BINARYTREE_DECOMPRESSION_H_

typedef struct BinaryTree BinaryTree;

BinaryTree* create_empty_tree();

BinaryTree* create_bt_node(unsigned char item, int flag);

//BinaryTree* remake_tree(BinaryTree *bt, unsigned char *string, int size, int backslash, int ni);


#endif /* BINARYTREE_DECOMPRESSION_H_ */
