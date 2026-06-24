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

/*
 * Descripcion: Define la estructura RoutesGraph con su matriz de adyacencia, las constantes MAX_VERTICES e INF, y declara las funciones de gestion del grafo y del algoritmo de Dijkstra.
 * Entradas: Punteros a RoutesGraph, nombres de puntos char* y pesos enteros segun la funcion.
 * Salidas: Enteros de exito/fallo o impresion en consola segun la funcion.
 * Restricciones: Requiere stdio.h. El grafo soporta un maximo de MAX_VERTICES vertices y representa distancias ausentes con el valor INF.
 */