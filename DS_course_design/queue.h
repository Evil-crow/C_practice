#ifndef _QUEUE_H
#define _QUEUE_H
#define MAXSIZE 20
typedef struct {
    int data[MAXSIZE];
    int queue_front;
    int queue_rear;
}Queue;

int queue_empty(Queue *Q);

void queue_init(Queue **Q);

void queue_push_in(Queue *Q, int data);

void queue_pop_out(Queue *Q, int *dest);

#endif
