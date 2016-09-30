/*
 * HuffmanList.h
 *
 *  Created on: 28 de set de 2016
 *      Author: rodolfomoreira
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct Node Node;

Node* create_linked_list();

Node* insert_item(Node *node, unsigned char item, int priority);

Node* char_list(Node *list, int *frequency);

void bubble_sort(Node *first);

#endif /* LINKEDLIST_H_ */
