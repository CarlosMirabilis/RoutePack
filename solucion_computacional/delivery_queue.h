#ifndef DELIVERY_QUEUE_H
#define DELIVERY_QUEUE_H
#include "package.h"
typedef struct QueueNode {
    Package data;
    struct QueueNode* next;
} QueueNode;
typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} DeliveryQueue;
void initQueue(DeliveryQueue* queue);
int enqueue(DeliveryQueue* queue, Package p);
int dequeue(DeliveryQueue* queue, Package* result);
QueueNode* peekQueue(DeliveryQueue* queue);
void displayQueue(DeliveryQueue* queue);
int isQueueEmpty(DeliveryQueue* queue);
#endif