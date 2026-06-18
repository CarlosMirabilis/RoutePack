#include "package.h"
void printPackage(Package p) {
    printf("Code: %s\n", p.code);
    printf("Client ID: %s\n", p.clientId);
    printf("Recipient Name: %s\n", p.recipientName);
    printf("Destination: %s\n", p.destination);
    printf("Weight: %.2f kg\n", p.weight);
    printf("Priority: %d\n", p.priority);
    printf("Status: ");
    switch (p.status) {
        case REGISTERED:
            printf("Registered\n");
            break;
        case PENDING_DELIVERY:
            printf("Pending Delivery\n");
            break;
        case IN_ROUTE:
            printf("In Route\n");
            break;
        case DELIVERED:
            printf("Delivered\n");
            break;
        case RETURNED:
            printf("Returned\n");
            break;
    }
}