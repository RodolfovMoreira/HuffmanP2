#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

typedef struct Q_Node Q_Node;

typedef struct Hashtable Hashtable;

Q_Node* create_queue();

Q_Node* enqueue(Q_Node* queue, unsigned char item);

#endif /* PRIORITYQUEUE_H_ */
