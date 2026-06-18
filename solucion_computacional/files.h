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