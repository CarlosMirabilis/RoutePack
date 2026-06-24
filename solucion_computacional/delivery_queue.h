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

/*
 * Descripcion: Define las estructuras QueueNode y DeliveryQueue, y declara las funciones de gestion de la cola de entregas.
 * Entradas: Punteros a DeliveryQueue y estructuras Package segun la funcion.
 * Salidas: Enteros de exito/fallo o punteros a QueueNode segun la funcion.
 * Restricciones: Depende de package.h. Debe incluirse antes de usar cualquier funcion del modulo delivery_queue.c.
 */