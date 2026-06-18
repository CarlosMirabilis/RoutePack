#include "package_avl.h"
#include <stdlib.h>
#include <string.h>
void initAVL(PackageAVL* avl) {
    avl->root = NULL;
}
int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}
int getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}
int updateHeight(AVLNode* node) {
    if (node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
    return node ? node->height : 0;
}
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x; // New root
}
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y; // New root
}
AVLNode* insertAVLNode(AVLNode* node, Package p) {
    if (!node) {
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        newNode->data = p;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1; // New node is initially added at leaf
        return newNode;
    }

    if (strcmp(p.code, node->data.code) < 0) {
        node->left = insertAVLNode(node->left, p);
    } else if (strcmp(p.code, node->data.code) > 0) {
        node->right = insertAVLNode(node->right, p);
    } else {
        return node; // Duplicate codes are not allowed
    }

    updateHeight(node);

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && strcmp(p.code, node->left->data.code) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(p.code, node->right->data.code) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(p.code, node->left->data.code) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(p.code, node->right->data.code) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Return the unchanged node pointer
}
AVLNode* searchAVL(PackageAVL* avl, char* code) {
    AVLNode* current = avl->root;
    while (current) {
        if (strcmp(code, current->data.code) == 0) {
            return current; // Package found
        }
        if (strcmp(code, current->data.code) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL; // Package not found
}
void inorderAVL(AVLNode* node) {
    if (node) {
        inorderAVL(node->left);
        printPackage(node->data);
        inorderAVL(node->right);
    }
}
int insertAVL(PackageAVL* avl, Package p) {
    if (searchAVL(avl, p.code) != NULL) {
        return 0; // Package with this code already exists
    }
    avl->root = insertAVLNode(avl->root, p);
    return 1; // Success
}