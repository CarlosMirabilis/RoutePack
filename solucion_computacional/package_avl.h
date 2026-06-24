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

/*
 * Descripcion: Define las estructuras AVLNode y PackageAVL, y declara las funciones de gestion del arbol AVL de paquetes.
 * Entradas: Punteros a PackageAVL o AVLNode, estructuras Package y cadenas char* segun la funcion.
 * Salidas: Enteros de exito/fallo o punteros a AVLNode segun la funcion.
 * Restricciones: Depende de package.h. Debe incluirse antes de usar cualquier funcion del modulo package_avl.c.
 */