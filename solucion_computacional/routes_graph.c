#include "routes_graph.h"
#include <string.h>
#include <stdlib.h>
void initGraph(RoutesGraph* graph) {
    graph->vertexCount = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->adjMatrix[i][j] = (i == j) ? 0 : INF;
        }
    }
}
int addVertex(RoutesGraph* graph, char* name) {
    if (graph->vertexCount >= MAX_VERTICES) {
        return 0; // Graph is full
    }
    strcpy(graph->names[graph->vertexCount], name);
    graph->vertexCount++;
    return 1; // Success
}
int addEdge(RoutesGraph* graph, char* from, char* to, int weight) {
    int fromIndex = findVertex(graph, from);
    int toIndex = findVertex(graph, to);
    if (fromIndex == -1 || toIndex == -1) {
        return 0; // One or both vertices not found
    }
    graph->adjMatrix[fromIndex][toIndex] = weight;
    graph->adjMatrix[toIndex][fromIndex] = weight; // For undirected graph
    return 1; // Success
}
int findVertex(RoutesGraph* graph, char* name) {
    for (int i = 0; i < graph->vertexCount; i++) {
        if (strcmp(graph->names[i], name) == 0) {
            return i;
        }
    }
    return -1; // Vertex not found
}
void displayVertices(RoutesGraph* graph) {
    printf("Vertices:\n");
    for (int i = 0; i < graph->vertexCount; i++) {
        printf("%d: %s\n", i, graph->names[i]);
    }
}
void displayMatrix(RoutesGraph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertexCount; i++) {
        for (int j = 0; j < graph->vertexCount; j++) {
            if (graph->adjMatrix[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", graph->adjMatrix[i][j]);
            }
        }
        printf("\n");
    }
}
void dijkstra(RoutesGraph* graph, char* origin, char* destination) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int prev[MAX_VERTICES];
    int originIndex = findVertex(graph, origin);
    int destinationIndex = findVertex(graph, destination);
    if (originIndex == -1 || destinationIndex == -1) {
        printf("Punto de origen o destino no encontrado.\n");
        return;
    }
    for (int i = 0; i < graph->vertexCount; i++) {
        dist[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[originIndex] = 0;
    for (int i = 0; i < graph->vertexCount; i++) {
        int minDist = INF;
        int minIndex = -1;
        for (int j = 0; j < graph->vertexCount; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        if (minIndex == -1) {
            break; // No more reachable vertices
        }
        visited[minIndex] = 1;
        for (int j = 0; j < graph->vertexCount; j++) {
            if (!visited[j] && graph->adjMatrix[minIndex][j] != INF) {
                int alt = dist[minIndex] + graph->adjMatrix[minIndex][j];
                if (alt < dist[j]) {
                    dist[j] = alt;
                    prev[j] = minIndex;
                }
            }
        }
    }
    if (dist[destinationIndex] == INF) {
        printf("No existe ruta entre %s y %s.\n", origin, destination);
        return;
    }
    int path[MAX_VERTICES];
    int pathIndex = 0;
    int current = destinationIndex;
    while (current != -1) {
        path[pathIndex++] = current;
        current = prev[current];
    }
    printf("Ruta mas corta: ");
    for (int i = pathIndex - 1; i >= 0; i--) {
        printf("%s", graph->names[path[i]]);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\n");
    printf("Distancia total: %d\n km\n", dist[destinationIndex]);
}