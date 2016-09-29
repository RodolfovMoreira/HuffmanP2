#ifndef HUFFMANFUNCTIONS_H_
#define HUFFMANFUNCTIONS_H_

typedef struct Q_Node Q_Node;

typedef struct Character Character;

int is_bit_set(unsigned char bits, int position);

int set_bit(unsigned char bits, int position);

Character* new_character(int *bytes, int index); // 'Estufa' os bits no unsigned char

Q_Node* create_queue();

Q_Node* enqueue(Q_Node* queue, unsigned char item);

void bubble_sort(Node *first);

Node* sort_tree(Node *root);

Node* merge_nodes(Node *first);

int tree_size(Node *tree, int size);

void print_pre_order(Node *tree, FILE *printing);

void codify(Node *tree, Hashtable *ht, int *byte, int i);

int* decimal_to_binary(int decimal, int *binary, int index);


#endif /* HUFFMANFUNCTIONS_H_ */
