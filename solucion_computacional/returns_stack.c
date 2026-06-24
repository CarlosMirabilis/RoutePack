#include "returns_stack.h"
#include <stdlib.h>
#include <string.h>
void initStack(ReturnsStack* stack) {
    stack->top = NULL;
    stack->size = 0;
}
int isStackEmpty(ReturnsStack* stack) {
    return stack->size == 0;
}
int push(ReturnsStack* stack, Package p) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        return 0; // Failed
    }
    newNode->data = p;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    return 1; // Success
}
int pop(ReturnsStack* stack, Package* result) {
    if (isStackEmpty(stack)) {
        return 0; // Stack is empty
    }
    StackNode* temp = stack->top;
    *result = temp->data; // Copy data to result
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return 1; // Success
}
StackNode* peekStack(ReturnsStack* stack) {
    return stack->top;
}
void displayStack(ReturnsStack* stack) {
    StackNode* current = stack->top;
    while (current) {
        printPackage(current->data);
        current = current->next;
    }
}

/*
 * Descripcion: Implementa la pila LIFO de paquetes devueltos.
 * Entradas: Punteros a ReturnsStack y estructuras Package segun la funcion.
 * Salidas: Enteros de exito/fallo, punteros a StackNode, o impresion en consola segun la funcion.
 * Restricciones: La pila debe inicializarse con initStack() antes de usarse.
 */