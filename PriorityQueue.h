#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

typedef struct Character Character;

typedef struct Hashtable Hashtable;

typedef struct Q_Node Q_Node;

Q_Node* create_queue();

Q_Node* enqueue(Q_Node* queue, unsigned char item);

Q_Node* text_queue(FILE *reading, Q_Node *queue, Hashtable *ht);

Q_Node* compressed_queue(FILE *copying, Q_Node *D_Queue);

#endif /* PRIORITYQUEUE_H_ */
