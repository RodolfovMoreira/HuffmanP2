#ifndef HUFFMAN_FUNCTIONS_H_
#define HUFFMAN_FUNCTIONS_H_


// --------- ESTRUTURAS -----------

typedef struct Character Character;

typedef struct Hashtable Hashtable;

typedef struct Node Node;

typedef struct Q_Node Q_Node;

typedef struct BinaryTree BinaryTree;

//------ BITSHIFT OPERATORS ------

int set_bit(unsigned char bits, int position);

int is_bit_set(unsigned char bits, int position);


// ------------  HUFFMAN FUNCTIONS  -----------------

void char_frequency(FILE *counting, int *frequency);

Character* new_character(int *byte, int index);

void codify(Node *tree, Hashtable *ht, int *byte, int i);

void decimal_to_binary(int decimal, int *binary, int index);

void create_huff(FILE *writing, int *binary, Node *root, Q_Node *queue);

Node* unique_char(Node *root);

void compress();

// --------- DECOMPRESSION ----------

int sizeof_trash(Q_Node *queue);

int sizeof_tree(Q_Node *queue);

void navigate_on_tree(FILE *newout, BinaryTree *root, Q_Node *queue, int size);

BinaryTree* remake_tree(BinaryTree *bt, unsigned char *string, int size, int backslash);

void decompress();

#endif /* HUFFMAN_FUNCTIONS_H_ */
