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
        default:
            printf("Unknown\n");
            break;
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

/*
 * Descripcion: Implementa la impresion en consola de todos los campos de un paquete.
 * Entradas: Una estructura Package recibida por valor.
 * Salidas: Impresion directa en consola; no retorna ningun valor.
 * Restricciones: Si el campo status contiene un valor fuera del enum PackageStatus, imprime "Unknown".
 */