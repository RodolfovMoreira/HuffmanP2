/*
 * HuffmanList.h
 *
 *  Created on: 28 de set de 2016
 *      Author: rodolfomoreira
 */

#ifndef HUFFMANLIST_H_
#define HUFFMANLIST_H_

typedef struct Node Node;

Node* create_linked_list();

Node* insert_item(Node *node, unsigned char item, int priority);

void print_linked_list(Node *first);

void bubble_sort(Node *first);

void print_pre_order(Node *tree, FILE *printing);


#endif /* HUFFMANLIST_H_ */
