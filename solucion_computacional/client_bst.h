#ifndef CLIENT_BST_H
#define CLIENT_BST_H
#include "stdio.h"
typedef struct {
    char id[15];
    char fullName[50];
    char phone[15];
    char email[50];
    char address[50];
} Client;
typedef struct ClientNode {
    Client data;
    struct ClientNode* left;
    struct ClientNode* right;
} ClientNode;
typedef struct {
    ClientNode* root;
} ClientBST;
void initBST(ClientBST* bst);
int insertClient(ClientBST* bst, Client c);
ClientNode* searchClient(ClientBST* bst, char* id);
void inorder (ClientNode* node);
void preorder (ClientNode* node);
void postorder (ClientNode* node);
int clientExists(ClientBST* bst, char* id);
#endif

/*
 * Descripcion: Define las estructuras Client, ClientNode y ClientBST, y declara las funciones de gestion del arbol BST de clientes.
 * Entradas: Punteros a ClientBST, estructuras Client y cadenas char* segun la funcion.
 * Salidas: Enteros de exito/fallo o punteros a ClientNode segun la funcion.
 * Restricciones: Requiere stdio.h. Debe incluirse antes de usar cualquier funcion del modulo client_bst.c.
 */