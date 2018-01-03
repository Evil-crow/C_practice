#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void queue_init(Queue **Q)
{
    (*Q) = (Queue *)malloc(sizeof(Queue));
    (*Q)->queue_front = 0;
    (*Q)->queue_rear = 0;
}

int queue_empty(Queue *Q)
{
    if (Q->queue_front == Q->queue_rear)
        return 1;
    return 0;
}

void queue_push_in(Queue *Q, int data)
{
    Q->data[Q->queue_rear++] = data;
}

void queue_pop_out(Queue *Q, int *dest)
{
    *dest = Q->data[Q->queue_front++];
}
