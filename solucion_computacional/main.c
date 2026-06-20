#include <stdio.h>
#include "package.h"
#include "package_list.h"
#include "delivery_queue.h"
#include "returns_stack.h"
#include "client_bst.h"
#include "package_avl.h"
#include "routes_graph.h"
#include "files.h"
#include "string.h"

#define CLIENTS_FILE "clients.txt"
#define PACKAGES_FILE "packages.txt"
#define GRAPH_FILE "graph.txt"

void readLine(char* buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
}

int main() {
    // Declarar todas las estructuras
    PackageList packageList;
    DeliveryQueue deliveryQueue;
    ReturnsStack returnsStack;
    ClientBST clientBST;
    PackageAVL packageAVL;
    RoutesGraph routesGraph;

    // Inicializar todas antes de usarlas
    initList(&packageList);
    initQueue(&deliveryQueue);
    initStack(&returnsStack);
    initBST(&clientBST);
    initAVL(&packageAVL);
    initGraph(&routesGraph);

    // TODO: cargar datos guardados con load... antes de mostrar el menú
    loadClients(&clientBST, CLIENTS_FILE);
    loadPackages(&packageList, PACKAGES_FILE);
    loadGraph(&routesGraph, GRAPH_FILE);

    for (PackageNode* node = packageList.head; node; node = node->next) {
        insertAVL(&packageAVL, node->data);
    }

    int option;
    do {
        printf("\n===== ROUTEPACK =====\n");
        printf("1. Gestionar clientes\n");
        printf("2. Gestionar paquetes\n");
        printf("3. Cola de entregas\n");
        printf("4. Devoluciones\n");
        printf("5. Puntos y rutas\n");
        printf("6. Ruta mas corta (Dijkstra)\n");
        printf("7. Reportes\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &option);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
        switch (option) {
            case 1: {
                int subOption;
                do {
                    printf("\n--- Gestionar Clientes ---\n");
                    printf("1. Insertar cliente\n");
                    printf("2. Buscar cliente por ID\n");
                    printf("3. Mostrar clientes (inorden)\n");
                    printf("4. Mostrar clientes (preorden)\n");
                    printf("5. Mostrar clientes (postorden)\n");
                    printf("0. Volver al menu principal\n");
                    printf("Seleccione una opcion: ");
                    scanf("%d", &subOption);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
                    switch (subOption) {
                        case 1: {
                            Client newClient;
                            printf("Ingrese el ID del cliente: ");
                            readLine(newClient.id, sizeof(newClient.id));
                            printf("Ingrese el nombre completo del cliente: ");
                            readLine(newClient.fullName, sizeof(newClient.fullName));
                            printf("Ingrese el telefono del cliente: ");
                            readLine(newClient.phone, sizeof(newClient.phone));
                            printf("Ingrese el email del cliente: ");
                            readLine(newClient.email, sizeof(newClient.email));
                            printf("Ingrese la direccion del cliente: ");
                            readLine(newClient.address, sizeof(newClient.address));
                            int result = insertClient(&clientBST, newClient);
                            if (result) {
                                printf("Cliente insertado exitosamente.\n");
                            } else {
                                printf("Error: El cliente ya existe o no se pudo insertar.\n");
                            }
                        }
                             break;
                        case 2: {
                            char searchId[10];
                            printf("Ingrese el ID del cliente a buscar: ");
                            readLine(searchId, sizeof(searchId));
                            ClientNode* foundClient = searchClient(&clientBST, searchId);
                            if (foundClient != NULL) {
                                printf("ID: %s\n", foundClient->data.id);
                                printf("Nombre: %s\n", foundClient->data.fullName);
                                printf("Telefono: %s\n", foundClient->data.phone);
                                printf("Email: %s\n", foundClient->data.email);
                                printf("Direccion: %s\n", foundClient->data.address);
                            } else {
                            printf("Cliente con ID %s no encontrado.\n", searchId);
                            }
                        }
                             break;
                        case 3:
                             inorder(clientBST.root);
                             break;
                        case 4:
                            preorder(clientBST.root);
                            break;
                        case 5:
                             postorder(clientBST.root);
                            break;
                        case 0:
                             break;
                        default:
                            printf("Opcion invalida.\n");
                    }
                 } while (subOption != 0);
                break;
            }
            case 2: {
                int subOption;
                do {
                    printf("\n--- Gestionar Paquetes ---\n");
                    printf("1. Registrar paquete\n");
                    printf("2. Mostrar lista de paquetes\n");
                    printf("3. Buscar paquete por codigo\n");
                    printf("4. Modificar estado de paquete\n");
                    printf("5. Eliminar paquete\n");
                    printf("6. Contar paquetes por estado\n");
                    printf("0. Volver al menu principal\n");
                    printf("Seleccione una opcion: ");
                    scanf("%d", &subOption);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
                    switch (subOption) {
                        case 1: {
                            Package newPackage;
                            printf("Ingrese el codigo del paquete: ");
                            readLine(newPackage.code, sizeof(newPackage.code));
                            printf("Ingrese el ID del cliente asociado: ");
                            readLine(newPackage.clientId, sizeof(newPackage.clientId));
                            if (!clientExists(&clientBST, newPackage.clientId)) {
                                printf("Error: No existe un cliente con ID %s.\n", newPackage.clientId);
                                break;
                            }
                        printf("Ingrese el nombre del destinatario: ");
                        readLine(newPackage.recipientName, sizeof(newPackage.recipientName));
                        printf("Ingrese la direccion de destino: ");
                        readLine(newPackage.destination, sizeof(newPackage.destination));
                        printf("Ingrese el peso del paquete: ");
                        scanf("%f", &newPackage.weight);
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("Ingrese la prioridad del paquete: ");        
                        scanf("%d", &newPackage.priority);                   
                        while ((c = getchar()) != '\n' && c != EOF);         
                        newPackage.status = REGISTERED;
                        if (insertPackage(&packageList, newPackage)) {
                            insertAVL(&packageAVL, newPackage);
                            printf("Paquete registrado exitosamente.\n");
                        } else {
                            printf("Error: El paquete ya existe o no se pudo registrar.\n");
                        }
                        }
                             break;
                        case 2:
                             displayList(&packageList);
                                break;
                        case 3: {
                            char searchCode[10];
                            printf("Ingrese el codigo del paquete a buscar: ");
                            readLine(searchCode, sizeof(searchCode));
                            PackageNode* foundPackage = searchPackage(&packageList, searchCode);
                            if (foundPackage != NULL) {
                                printPackage(foundPackage->data);
                            } else {
                                printf("Paquete con codigo %s no encontrado.\n", searchCode);
                            }
                        }
                                break;
                        case 4: {
                            char code[10];
                            printf("Ingrese el codigo del paqueteo: ");
                            readLine(code, sizeof(code));
                            if (!searchPackage(&packageList, code)) {
                                printf("Error: No existe un paquete con codigo %s.\n", code);
                                break;
                            }
                            printf("0. Registrado\n1. Pendiente de entrega\n2. En ruta\n3. Entregado\n4. Devuelto\n");
                            printf("Nuevo estado: ");
                            int newStatus;
                            scanf("%d", &newStatus);
                            while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
                            if (updateStatus(&packageList, code, (PackageStatus)newStatus)) {
                                printf("Estado del paquete actualizado exitosamente.\n");
                            } else {
                                printf("Error: No se pudo actualizar el estado del paquete.\n");
                            }
                        }
                                break;
                        case 5: {
                            char code[10];
                            printf("Ingrese el codigo del paquete a eliminar: ");
                            readLine(code, sizeof(code));
                            if (deletePackage(&packageList, code)) {
                                printf("Paquete eliminado exitosamente.\n");
                            } else {
                                printf("Error: Paquete no encontrado.\n");
                            }
                        }
                                break;  
                        case 6: 
                            printf("Registrados: %d\n", countByStatus(&packageList, REGISTERED));
                            printf("Pendientes de entrega: %d\n", countByStatus(&packageList, PENDING_DELIVERY));
                            printf("En ruta: %d\n", countByStatus(&packageList, IN_ROUTE));
                            printf("Entregados: %d\n", countByStatus(&packageList, DELIVERED));
                            printf("Devueltos: %d\n", countByStatus(&packageList, RETURNED));
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcion invalida.\n");
                    }
                } while (subOption != 0);
                break;
            }
            case 3: {
                int subOption;
                do {
                    printf("\n--- Cola de Entregas ---\n");
                    printf("1. Encolar paquete para entrega\n");
                    printf("2. Mostrar cola de entregas\n");
                    printf("3. Ver siguiente paquete a entregar\n");
                    printf("4. Procesar entrega (desencolar)\n");
                    printf("0. Volver al menu principal\n");
                    printf("Seleccione una opcion: ");
                    scanf("%d", &subOption);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
                    switch (subOption) {
                        case 1: {
                            char code[10];
                            printf("Ingrese el codigo del paquete a encolar: ");
                            readLine(code, sizeof(code));
                            PackageNode* foundPackage = searchPackage(&packageList, code);
                            if (!foundPackage) {
                                printf("Error: No existe un paquete con codigo %s.\n", code);
                                break;
                            }
                            updateStatus(&packageList, code, PENDING_DELIVERY);
                            foundPackage->data.status = PENDING_DELIVERY;
                            if (enqueue(&deliveryQueue, foundPackage->data)) {
                                printf("Paquete encolado para entrega.\n");
                            } else {
                                printf("Error: No se pudo encolar el paquete.\n");
                            }
                        }
                            break;
                        case 2:
                            displayQueue(&deliveryQueue);
                            break;
                        case 3: {
                            QueueNode* nextPackage = peekQueue(&deliveryQueue);
                            if (nextPackage) {
                               printPackage(nextPackage->data);
                            } else {
                                printf("La cola de entregas esta vacia.\n");
                            }   
                        }
                            break;
                        case 4: {
                            Package processedPackage;
                            if (!dequeue(&deliveryQueue, &processedPackage)) {
                                printf("La cola de entregas esta vacia.\n");
                                break;
                            }
                            printf("Procesando entrega de %s. Fue exitosa? (s/n): ", processedPackage.code);
                            char answer[10];
                            readLine(answer, sizeof(answer));
                            if (answer[0] == 's' || answer[0] == 'S') {
                                processedPackage.status = DELIVERED;
                                updateStatus(&packageList, processedPackage.code, DELIVERED);
                                printf("Entrega marcada como exitosa.\n");
                            } else {
                                processedPackage.status = RETURNED;
                                updateStatus(&packageList, processedPackage.code, RETURNED);
                                push(&returnsStack, processedPackage);
                                printf("Entrega fallida. Paquete enviado a devoluciones.\n");
                            }
                        }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcion invalida.\n");
                    }
                } while (subOption != 0);
                break;
            }
            case 4: {
                int subOption;
                do {
                    printf("\n--- Devoluciones ---\n");
                    printf("1. Mostrar devoluciones (LIFO)\n");
                    printf("2. Ver ultimo paquete devuelto\n");
                    printf("3. Desapilar y reencolar para entrega\n");
                    printf("0. Volver al menu principal\n");
                    printf("Seleccione una opcion: ");
                    scanf("%d", &subOption);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
                    switch (subOption) {
                        case 1:
                            displayStack(&returnsStack);
                            break;
                        case 2: {
                            StackNode* lastReturn = peekStack(&returnsStack);
                            if (lastReturn) {
                                printPackage(lastReturn->data);
                            } else {
                                printf("No hay paquetes devueltos.\n");
                            }
                        }
                            break;
                        case 3: {
                            Package returnPackage;
                            if (!pop(&returnsStack, &returnPackage)) {
                                printf("No hay paquetes devueltos.\n");
                                break;
                            }
                            returnPackage.status = PENDING_DELIVERY;
                            updateStatus(&packageList, returnPackage.code, PENDING_DELIVERY);
                            if (enqueue(&deliveryQueue, returnPackage)) {
                                printf("Paquete reencolado para entrega.\n");
                            } else {
                                printf("Error: No se pudo encolar el paquete.\n");
                            }
                       }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcion invalida.\n");
                    }
                } while (subOption != 0);
                    break;
            }
            case 5: {
                int subOption;
                do {
                    printf("\n--- Puntos y Rutas ---\n");
                    printf("1. Agregar punto\n");
                    printf("2. Agregar ruta entre puntos\n");
                    printf("3. Mostrar puntos\n");
                    printf("4. Mostrar matriz de adyacencia\n");
                    printf("0. Volver al menu principal\n");
                    printf("Seleccione una opcion: ");
                    scanf("%d", &subOption);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
                    switch (subOption) {
                        case 1: {
                            char pointName[50];
                            printf("Ingrese el nombre del punto: ");
                            readLine(pointName, sizeof(pointName));
                            if (addVertex(&routesGraph, pointName)) {
                                printf("Punto agregado exitosamente.\n");
                            } else {
                                printf("Error: No se pudo agregar el punto (posiblemente ya existe o se alcanzo el maximo).\n");
                            }
                        }
                            break;
                        case 2: {
                            char from[50], to[50];
                            int weight;
                            printf("Ingrese el punto de origen: ");
                            readLine(from, sizeof(from));
                            printf("Ingrese el punto de destino: ");
                            readLine(to, sizeof(to));
                            printf("Ingrese la distancia entre los puntos (km): ");
                            scanf("%d", &weight);
                            while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
                            if (addEdge(&routesGraph, from, to, weight)) {
                                printf("Ruta agregada exitosamente.\n");
                            } else {
                                printf("Error: No se pudo agregar la ruta (verifique que ambos puntos existan).\n");
                            }
                        }
                             break;
                        case 3:
                             displayVertices(&routesGraph);
                             break;
                        case 4:
                             displayMatrix(&routesGraph);
                             break;
                        case 0:
                             break;
                        default:
                             printf("Opcion invalida.\n");
                    }
                } while (subOption != 0);
                break;
            }
            case 6: {
                char origin[50], destination[50];
                printf("Ingrese el punto de origen: ");
                readLine(origin, sizeof(origin));
                printf("Ingrese el punto de destino: ");
                readLine(destination, sizeof(destination));
                dijkstra(&routesGraph, origin, destination);
            }
                break;
            case 7:{
                int subOption;
                do {
                    printf("\n--- Reportes ---\n");
                    printf("1. Total de paquetes registrados\n");
                    printf("2. Total de paquetes entregados\n");
                    printf("3. Total de paquetes pendientes\n");
                    printf("4. Total de paquetes devueltos\n");
                    printf("5. Clientes registrados (BST inorden)\n");
                    printf("6. Paquetes registrados (AVL inorden)\n");
                    printf("7. Ruta más corta entre dos puntos\n");
                    printf("0. Volver al menu principal\n");
                    printf("Seleccione una opcion: ");
                    scanf("%d", &subOption);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Limpiar el buffer de entrada
                    switch (subOption) {
                        case 1:
                            printf("Total de paquetes registrados: %d\n", packageList.size);
                            break;
                        case 2: {
                            int count = 0;
                            for (PackageNode* node = packageList.head; node; node = node->next) {
                                if (node->data.status == DELIVERED) {
                                    count++;
                                }
                            }
                            printf("Total de paquetes entregados: %d\n", count);
                            break;
                        }
                        case 3: {
                            int count = 0;
                            for (PackageNode* node = packageList.head; node; node = node->next) {
                                if (node->data.status == PENDING_DELIVERY) {
                                    count++;
                                }
                            }
                            printf("Total de paquetes pendientes: %d\n", count);
                            break;
                        }
                        case 4: {
                            int count = 0;
                            for (PackageNode* node = packageList.head; node; node = node->next) {
                                if (node->data.status == RETURNED) {
                                    count++;
                                }
                            }
                            printf("Total de paquetes devueltos: %d\n", count);
                            break;
                        }
                        case 5:
                             inorder(clientBST.root);
                             break;
                        case 6:
                             inorderAVL(packageAVL.root);
                             break;
                        case 7: {
                             char origin[50], destination[50];
                             printf("Ingrese el punto de origen: ");
                             readLine(origin, sizeof(origin));
                             printf("Ingrese el punto de destino: ");
                             readLine(destination, sizeof(destination));
                             dijkstra(&routesGraph, origin, destination);
                             break;
                        }
                        case 0:
                             break;
                        default:
                             printf("Opcion invalida.\n");
                    }
            }while (subOption != 0);
                break;
            }
            case 0:
                printf("Guardando datos...\n");
                saveClients(&clientBST, CLIENTS_FILE);
                savePackages(&packageList, PACKAGES_FILE);
                saveGraph(&routesGraph, GRAPH_FILE);
                printf("Datos guardados. Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (option != 0);

    return 0;
}