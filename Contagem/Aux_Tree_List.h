#ifndef AUX_TREE_LIST_H_
#define AUX_TREE_LIST_H_

typedef struct LinkedList LinkedList;

LinkedList* InitializeList();

LinkedList* CreateNode(LinkedList *first, int item);

int Peek(LinkedList *first);

LinkedList* RemoveNode(LinkedList *first);

int IsListEmpty(LinkedList *first);

#endif /* AUX_TREE_LIST_H_ */
