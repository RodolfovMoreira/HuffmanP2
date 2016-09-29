#ifndef HUFFMANFUNCTIONS_H_
#define HUFFMANFUNCTIONS_H_

typedef struct Q_Node Q_Node;

typedef struct Character Character;

int is_bit_set(unsigned char bits, int position);

int set_bit(unsigned char bits, int position);

Character* new_character(int *bytes, int index); // 'Estufa' os bits no unsigned char

Q_Node* create_queue();

Q_Node* enqueue(Q_Node* queue, unsigned char item);

Q_Node* text_queue(FILE *reading, Q_Node *queue, Hashtable *ht);

Node* sort_tree(Node *root);

Node* merge_nodes(Node *first);

int tree_size(Node *tree, int size);

void codify(Node *tree, Hashtable *ht, int *byte, int i);

int* decimal_to_binary(int decimal, int *binary, int index);

void char_frequency(FILE *counting, int *frequency);

Node* char_list(Node *list, int *frequency);

Node* make_tree(Node *root);

void create_huff(FILE *writing, int *binary, Node *root, Q_Node *queue);

void compress();

#endif /* HUFFMANFUNCTIONS_H_ */
