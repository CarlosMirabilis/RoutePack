#include "client_bst.h"
#include <stdlib.h>
#include <string.h>
void initBST(ClientBST* bst) {
    bst->root = NULL;
}
int insertClient(ClientBST* bst, Client c) {
    if (clientExists(bst, c.id)) {
        return 0; // Client already exists
    }
    ClientNode* newNode = (ClientNode*)malloc(sizeof(ClientNode));
    if (!newNode) {
        return 0; // Failed to allocate memory
    }
    newNode->data = c;
    newNode->left = NULL;
    newNode->right = NULL;

    if (!bst->root) {
        bst->root = newNode;
        return 1; // Success
    }

    ClientNode* current = bst->root;
    ClientNode* parent = NULL;

    while (current) {
        parent = current;
        if (strcmp(c.id, current->data.id) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (strcmp(c.id, parent->data.id) < 0) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return 1; // Success
}
ClientNode* searchClient(ClientBST* bst, char* id) {
    ClientNode* current = bst->root;
    while (current) {
        if (strcmp(id, current->data.id) == 0) {
            return current; // Client found
        }
        if (strcmp(id, current->data.id) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL; // Client not found
}
void inorder(ClientNode* node) {
    if (node) {
        inorder(node->left);
        printf("ID: %s, Name: %s\n", node->data.id, node->data.fullName);
        inorder(node->right);
    }
}
void preorder(ClientNode* node) {
    if (node) {
        printf("ID: %s, Name: %s\n", node->data.id, node->data.fullName);
        preorder(node->left);
        preorder(node->right);
    }
}
void postorder(ClientNode* node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        printf("ID: %s, Name: %s\n", node->data.id, node->data.fullName);
    }
}
int clientExists(ClientBST* bst, char* id) {
    return searchClient(bst, id) != NULL;
}

/*
 * Descripcion: Implementa el arbol binario de busqueda de clientes usando su ID como llave.
 * Entradas: Punteros a ClientBST y datos de tipo Client o char* segun la funcion.
 * Salidas: Enteros de exito/fallo, punteros a ClientNode, o impresion en consola segun la funcion.
 * Restricciones: No permite IDs duplicados. El arbol debe inicializarse con initBST() antes de usarse.
 */