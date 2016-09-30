#ifndef HUFFMANFUNCTIONS_H_
#define HUFFMANFUNCTIONS_H_


typedef struct Character Character;

typedef struct Q_Node Q_Node;

typedef struct Node Node;

//----------------------  BIT HANDLER FUNCTIONS -------------------------

void decimal_to_binary(int decimal, int *binary, int index);

Character* new_character(int *bytes, int index); // 'Estufa' os bits no unsigned char

void compress();

int is_bit_set(unsigned char bits, int position);

int set_bit(unsigned char bits, int position);

void codify(Node *tree, Hashtable *ht, int *byte, int i);

//------------------------- ARCHIVE LIBRARY ------------------------------

void char_frequency(FILE *counting, int *frequency);

void create_huff(FILE *writing, int *binary, Node *root, Q_Node *queue);

Q_Node* text_queue(FILE *reading, Q_Node *queue, Hashtable *ht);


#endif /* HUFFMANFUNCTIONS_H_ */
