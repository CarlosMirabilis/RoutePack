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

/*
 * Descripcion: Define el enum PackageStatus, la estructura Package y declara la funcion de impresion de paquetes.
 * Entradas: Una estructura Package por valor.
 * Salidas: Impresion directa en consola; no retorna ningun valor.
 * Restricciones: Requiere stdio.h. Es la dependencia base de la mayoria de los otros modulos del sistema.
 */