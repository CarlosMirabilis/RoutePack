#ifndef RETURNS_STACK_H
#define RETURNS_STACK_H
#include "package.h"
typedef struct StackNode {
    Package data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int size;
} ReturnsStack;
void initStack(ReturnsStack* stack);
int push(ReturnsStack* stack, Package p);
int pop(ReturnsStack* stack, Package* result);
StackNode* peekStack(ReturnsStack* stack);
void displayStack(ReturnsStack* stack);
int isStackEmpty(ReturnsStack* stack);
#endif

/*
 * Descripcion: Define las estructuras StackNode y ReturnsStack, y declara las funciones de gestion de la pila de devoluciones.
 * Entradas: Punteros a ReturnsStack y estructuras Package segun la funcion.
 * Salidas: Enteros de exito/fallo o punteros a StackNode segun la funcion.
 * Restricciones: Depende de package.h. Debe incluirse antes de usar cualquier funcion del modulo returns_stack.c.
 */