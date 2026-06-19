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
            case 2:

                // TODO: submenu de clientes (insertar, buscar, inorden/preorden/postorden)
                break;
            case 2:
                // TODO: submenu de paquetes (registrar, mostrar, buscar, modificar estado, eliminar, contar por estado)
                break;
            case 3:
                // TODO: submenu de cola (encolar, mostrar, ver siguiente, procesar entrega)
                break;
            case 4:
                // TODO: submenu de pila (mostrar, ver ultimo, desapilar y reencolar)
                break;
            case 5:
                // TODO: submenu de grafo (agregar punto, agregar ruta, mostrar puntos, mostrar matriz)
                break;
            case 6:
                // TODO: pedir origen y destino, llamar dijkstra()
                break;
            case 7:
                // TODO: menu de reportes (totales por estado, clientes BST, paquetes AVL inorden, ruta mas corta)
                break;
            case 0:
                printf("Guardando datos...\n");
                // TODO: guardar datos con save... antes de salir
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (option != 0);

    return 0;
}