#ifndef PACKAGE_H
#define PACKAGE_H
#include <stdio.h>
typedef enum {
    REGISTERED,
    PENDING_DELIVERY,
    IN_ROUTE,
    DELIVERED,
    RETURNED
} PackageStatus;
typedef struct {
    char code[10];
    char clientId[15];
    char recipientName[50];
    char destination[50];
    float weight;
    int priority;
    PackageStatus status;
} Package;
void printPackage(Package p);
#endif