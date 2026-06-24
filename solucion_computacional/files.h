#ifndef FILES_H
#define FILES_H
#include "client_bst.h"
#include "package_list.h"
#include "routes_graph.h"
void savePackages(PackageList* list, char* filename);
void loadPackages(PackageList* list, char* filename);
void saveClients(ClientBST* bst, char* filename);
void loadClients(ClientBST* bst, char* filename);
void saveGraph(RoutesGraph* graph, char* filename);
void loadGraph(RoutesGraph* graph, char* filename);
#endif

/*
 * Descripcion: Declara las funciones de guardado y carga en disco para clientes, paquetes y el grafo de rutas.
 * Entradas: Punteros a las estructuras correspondientes y el nombre del archivo como char*.
 * Salidas: Ninguna; los efectos se producen sobre los archivos en disco o en las estructuras cargadas.
 * Restricciones: Depende de client_bst.h, package_list.h y routes_graph.h. Los archivos de carga deben tener el formato que producen las funciones de guardado.
 */