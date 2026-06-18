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
int isStackEmpty(ReturnsStack* stack, Package p);
int pop(ReturnsStack* stack, Package* result);
StackNode* peekStack(ReturnsStack* stack);
void displayStack(ReturnsStack* stack);
int isStackEmpty(ReturnsStack* stack);
#endif