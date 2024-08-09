#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    int height;
    int val;
    struct node* left;
    struct node* right;
} Node;

int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(Node *n) {
    if (!n) return 0;
    return n->height;
}

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getBalanceFactor(Node* n) {
    if (!n) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right; 
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Rewiring the nodes
    y->left  = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return createNode(key);

    if (key < node->val) {
        node->left = insert(node->left, key);
    } else if (key > node->val) {
        node->right = insert(node->right, key);
    } else {
        return node; // Duplicate keys not allowed
    }

    // Update height of the current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Get balance factor of this node
    int bf = getBalanceFactor(node);

    // LL Rotation
    if (bf > 1 && key < node->left->val) {
        return rightRotate(node);
    }

    // RR Rotation
    if (bf < -1 && key > node->right->val) {
        return leftRotate(node);
    }

    // LR Rotation
    if (bf > 1 && key > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Rotation
    if (bf < -1 && key < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(Node* root) {
    if (root) {
        printf("%d ", root->val);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the AVL tree is:\n");
    return 0;
}
