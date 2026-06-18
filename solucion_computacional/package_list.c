#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "package_list.h"
void initList(PackageList* list) {
    list->head = NULL;
    list->size = 0;
}
int insertPackage(PackageList* list, Package p) {
    if (searchPackage(list, p.code) != NULL) {
        return 0;
    }
    PackageNode* newNode = (PackageNode*)malloc(sizeof(PackageNode));
    if (!newNode) {
        return 0; // Failed to allocate memory
    }
    newNode->data = p;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
    return 1; // Success
}
void displayList(PackageList* list) {
    PackageNode* current = list->head;
    while (current) {
        printPackage(current->data);
        current = current->next;
    }
}
PackageNode* searchPackage(PackageList* list, char* code) {
    PackageNode* current = list->head;
    while (current) {
        if (strcmp(current->data.code, code) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Package not found
}
int updateStatus(PackageList* list, char* code, PackageStatus newStatus) {
    PackageNode* node = searchPackage(list, code);
    if (node) {
        node->data.status = newStatus;
        return 1; // Success
    }
    return 0; // Package not found
}
int deletePackage(PackageList* list, char* code) {
    PackageNode* current = list->head;
    PackageNode* previous = NULL;

    while (current) {
        if (strcmp(current->data.code, code) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                list->head = current->next;
            }
            free(current);
            list->size--;
            return 1; // Success
        }
        previous = current;
        current = current->next;
    }
    return 0; // Package not found
}
int countByStatus(PackageList* list, PackageStatus status) {
    int count = 0;
    PackageNode* current = list->head;
    
    while (current) {
        if (current->data.status == status) {
            count++;
        }
        current = current->next;
    }
    
    return count;
}