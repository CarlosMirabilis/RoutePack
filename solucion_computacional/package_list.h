#ifndef PACKAGE_LIST_H
#define PACKAGE_LIST_H
#include "package.h"
typedef struct PackageNode {
    Package data;
    struct PackageNode* next;
} PackageNode;
typedef struct {
    PackageNode* head;
    int size;
} PackageList;
void initList(PackageList* list);
int insertPackage(PackageList* list, Package p);
void displayList(PackageList* list);
PackageNode* searchPackage(PackageList* list, char* code);
int updateStatus(PackageList* list, char* code, PackageStatus newStatus);
int deletePackage(PackageList* list, char* code);
int countByStatus(PackageList* list, PackageStatus status);
#endif