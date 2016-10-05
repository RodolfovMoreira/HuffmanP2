#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct Node Node;

Node* createLinkedList();

Node* InsertItem(Node *first, int item);

int search(Node *first, int item);


#endif /* LINKED_LIST_H_ */
