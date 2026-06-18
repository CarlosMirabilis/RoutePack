#ifndef CLIENT_BST_H
#define CLIENT_BST_H
#include "stdio.h"
typedef struct {
    char id[10];
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