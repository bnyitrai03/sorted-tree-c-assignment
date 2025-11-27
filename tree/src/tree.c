#include "tree.h"

/**
 * Please correct the contents of this file to make sure all functions here do what they are supposed to do if you find
 * that they do not work as expected.
 */

// Tree function: you are allowed to change the contents, but not the method signature
Tree* tree_create(){
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;

    return tree;
}

// Helper function: you are allowed to change this to your preferences
void tree_node_delete(Node* node) {
    if (node == NULL) return;

    free(node);

    tree_node_delete(node->left);
    tree_node_delete(node->right);
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_delete(Tree* tree) {
    tree_node_delete(tree->root);

    free(tree);
}

// Helper function: you are allowed to change this to your preferences
void node_insert(Node* node, int age, char* name) {
    if (age <= node->age){
        if (node->left == NULL){
            Node* newLeft = malloc(sizeof(Node));
            newLeft->age = age;
            newLeft->name = name;
            node->left = newLeft;
        } else {
            node_insert(node->left, age, name);
        }
    } else {
        if (node->right == NULL){
            Node* newRight = malloc(sizeof(Node));
            newRight->age = age;
            newRight->name = name;
            node->right = newRight;
        } else {
            node_insert(node->right, age, name);
        }
    }
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_insert(Tree* tree, int age, char* name) {
    if (tree->root == NULL) {
        Node *node = malloc(sizeof(Node));
        node->name = name;
        node->age = age;
        tree->root = node;
    } else {
        node_insert(tree->root, age, name);
    }
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_erase(Tree* tree, int age, char* name) {
    Node* data = tree_find(tree, age, name);

    free(data);
}

// Helper function: you are allowed to change this to your preferences
void tree_print_node(Node* node){
    if (node == NULL) {
        printf("null");
        return;
    }

    printf("[");
    printf("{\"%d\":\"%s\"},", node->age, node->name);
    tree_print_node(node->left);
    printf(",");
    tree_print_node(node->right);
    printf("]");
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_print(Tree* tree, int printNewline){
    if (tree == NULL) {
        printf("null");
        return;
    }

    tree_print_node(tree->root);

    if (printNewline){
        printf("\n");
    }
}

// Helper function: you are allowed to change this to your preferences
Node* node_find(Node* node, int age, char* name) {
    if (node->age == age && node->name == name) {
        return node;
    }

    if (age <= node->age) {
        return node_find(node->left, age, name);
    } else {
        return node_find(node->right, age, name);
    }
}

// Tree function: you are allowed to change the contents, but not the method signature
Node* tree_find(Tree* tree, int age, char* name) {
    return node_find(tree->root, age, name);
}
