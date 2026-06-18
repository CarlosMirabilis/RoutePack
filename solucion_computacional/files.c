#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_bst.h"
#include "package_list.h"
#include "routes_graph.h"
void savePackages(PackageList* list, char* filename) {
    FILE* file = fopen(filename
, "w");
    if (!file) {    
        printf("Error opening file for writing: %s\n", filename);
        return;
    }
    PackageNode* current = list->head;
    while (current) {
        fprintf(file, "%s,%s,%s,%s,%.2f,%d,%d\n",
                current->data.code,
                current->data.clientId,
                current->data.recipientName,
                current->data.destination,
                current->data.weight,
                current->data.priority,
                current->data.status);
        current = current->next;
    }
    fclose(file);
}
void loadPackages(PackageList* list, char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading: %s\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Package p;
        char* token = strtok(line, ",");
        if (token) strncpy(p.code, token, sizeof(p.code));
        token = strtok(NULL, ",");
        if (token) strncpy(p.clientId, token, sizeof(p.clientId));
        token = strtok(NULL, ",");
        if (token) strncpy(p.recipientName, token, sizeof(p.recipientName));
        token = strtok(NULL, ",");
        if (token) strncpy(p.destination, token, sizeof(p.destination));
        token = strtok(NULL, ",");
        if (token) p.weight = atof(token);
        token = strtok(NULL, ",");
        if (token) p.priority = atoi(token);
        token = strtok(NULL, ",");
        if (token) p.status = atoi(token);
        insertPackage(list, p);
    }
    fclose(file);
}
void saveClientNode(ClientNode* node, FILE* file) {
    if (node) {
        fprintf(file, "%s,%s,%s,%s,%s\n",
                node->data.id,
                node->data.fullName,
                node->data.phone,
                node->data.email,
                node->data.address);
        saveClientNode(node->left, file);
        saveClientNode(node->right, file);
    }
}

void saveClients(ClientBST* bst, char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }
    saveClientNode(bst->root, file);
    fclose(file);
}
void loadClients(ClientBST* bst, char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading: %s\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Client c;
        char* token = strtok(line, ",");
        if (token) strncpy(c.id, token, sizeof(c.id));
        token = strtok(NULL, ",");
        if (token) strncpy(c.fullName, token, sizeof(c.fullName));
        token = strtok(NULL, ",");
        if (token) strncpy(c.phone, token, sizeof(c.phone));
        token = strtok(NULL, ",");
        if (token) strncpy(c.email, token, sizeof(c.email));
        token = strtok(NULL, ",");
        if (token) {
            token[strcspn(token, "\n")] = '\0';
            strncpy(c.address, token, sizeof(c.address));
        }
        insertClient(bst, c);
    }
    fclose(file);
}
void saveGraph(RoutesGraph* graph, char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }
    fprintf(file, "%d\n", graph->vertexCount);
    for (int i = 0; i < graph->vertexCount; i++) {
        fprintf(file, "%s\n", graph->names[i]);
    }
    for (int i = 0; i < graph->vertexCount; i++) {
        for (int j = 0; j < graph->vertexCount; j++) {
            fprintf(file, "%d ", graph->adjMatrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}  
void loadGraph(RoutesGraph* graph, char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading: %s\n", filename);
        return;
    }
    fscanf(file, "%d\n", &graph->vertexCount);
    for (int i = 0; i < graph->vertexCount; i++) {
        fgets(graph->names[i], sizeof(graph->names[i]), file);
        graph->names[i][strcspn(graph->names[i], "\n")] = '\0'; // Remove newline
    }
    for (int i = 0; i < graph->vertexCount; i++) {
        for (int j = 0; j < graph->vertexCount; j++) {
            fscanf(file, "%d", &graph->adjMatrix[i][j]);
        }
    }
    fclose(file);
}
