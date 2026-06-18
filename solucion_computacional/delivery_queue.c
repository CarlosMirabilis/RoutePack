#include "delivery_queue.h"
#include <stdlib.h>
#include <string.h>
void initQueue(DeliveryQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}
int enqueue(DeliveryQueue* queue, Package p) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        return 0; // Failed
    }
    newNode->data = p;
    newNode->next = NULL;

    if (queue->rear) {
        queue->rear->next = newNode;
    } else {
        queue->front = newNode;
    }
    queue->rear = newNode;
    queue->size++;
    return 1; // Success
}
int dequeue(DeliveryQueue* queue, Package* result) {
    if (isQueueEmpty(queue)) {
        return 0; // Queue is empty
    }
    QueueNode* temp = queue->front;
    *result = temp->data; // Copy data to result
    queue->front = queue->front->next;
    if (!queue->front) {
        queue->rear = NULL; // Queue is now empty
    }
    free(temp);
    queue->size--;
    return 1; // Success
}
QueueNode* peekQueue(DeliveryQueue* queue) {
    return queue->front;
}
void displayQueue(DeliveryQueue* queue) {
    QueueNode* current = queue->front;
    while (current) {
        printPackage(current->data);
        current = current->next;
    }
}
int isQueueEmpty(DeliveryQueue* queue) {
    return queue->size == 0;
}
