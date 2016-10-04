#ifndef BINARYTREE_COMPRESSION_H_
#define BINARYTREE_COMPRESSION_H_

typedef struct Node Node;

Node* sort_tree(Node *root);

Node* merge_nodes(Node *first);

int tree_size(Node *tree, int size);

Node* make_tree(Node *root);

void print_pre_order(Node *tree, FILE *printing);

#endif /* BINARYTREE_COMPRESSION_H_ */
