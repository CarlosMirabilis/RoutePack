#ifndef PACKAGE_AVL_H
#define PACKAGE_AVL_H
#include "package.h"
typedef struct AVLNode {
    Package data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;
typedef struct {
    AVLNode* root;
} PackageAVL;
void initAVL(PackageAVL* avl);
int insertAVL(PackageAVL* avl, Package p);
AVLNode* searchAVL(PackageAVL* avl, char* code);
void inorderAVL(AVLNode* node);
#endif