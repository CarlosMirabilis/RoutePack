#ifndef ROUTES_GRAPH_H
#define ROUTES_GRAPH_H
#include "stdio.h"
#define MAX_VERTICES 20
#define INF 99999
typedef struct {
    char names[MAX_VERTICES][50];
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int vertexCount;
} RoutesGraph;
void initGraph(RoutesGraph* graph);
int addVertex(RoutesGraph* graph, char* name);
int addEdge(RoutesGraph* graph, char* from, char* to, int weight);
int findVertex(RoutesGraph* graph, char* name);
void displayVertices(RoutesGraph* graph);
void displayMatrix(RoutesGraph* graph);
void dijkstra(RoutesGraph* graph, char* origin, char* destination);
#endif