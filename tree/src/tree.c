#include "tree.h"

/**
 * Please correct the contents of this file to make sure all functions here do what they are supposed to do if you find
 * that they do not work as expected.
 */

// Tree function: you are allowed to change the contents, but not the method signature
Tree* tree_create(){
    Tree *tree = malloc(sizeof(Tree));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    return tree;
}

// Helper function: you are allowed to change this to your preferences
void tree_node_delete(Node* node) {
    if (node == NULL) return;

    // delete left and right subtree
    tree_node_delete(node->left);
    tree_node_delete(node->right);

    // free name and node
    free(node->name);
    free(node);
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_delete(Tree* tree) {
    if (tree == NULL) return;
    if (tree->root != NULL) {
        tree_node_delete(tree->root);
    }
    free(tree);
}

// Returns a new node or NULL on failure
Node* create_node(int age, const char *name) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL){
        fprintf(stderr, "Memory allocation failed for new node\n");
        return NULL;
    }

    node->name = malloc(strlen(name) + 1);
    if (node->name == NULL) {
        free(node);
        fprintf(stderr, "Memory allocation failed for node name\n");
        return NULL;
    }
    strncpy(node->name, name, (strlen(name) + 1));
    node->age  = age;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Helper function: you are allowed to change this to your preferences
void node_insert(Node* node, int age, char* name) {
    if (age == node->age) {
        fprintf(stderr, "Duplicate age ignored: %d\n", age);
        return;
    }

    if (age < node->age){
        if (node->left == NULL){
            node->left = create_node(age, name);
        } else {
            node_insert(node->left, age, name);
        }
    } else {
        if (node->right == NULL){
            node->right = create_node(age, name);
        } else {
            node_insert(node->right, age, name);
        }
    }
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_insert(Tree* tree, int age, char* name) {
    if (tree == NULL) return;
    if (tree->root == NULL) {
        tree->root = create_node(age, name);
    } else {
        node_insert(tree->root, age, name);
    }
}

// Biggest value in the left subtree
Node* get_predecessor(Node* current){
    current = current->left;
    while(current->right != NULL) current = current->right;
    return current;
}

Node* node_erase(Node* node, int age, char* name) {
    if(node == NULL || name == NULL) return NULL;

    // Find the node to delete
    if (age < node->age) {
        node->left = node_erase(node->left, age, name);
    } 
    else if (age > node->age) {
        node->right = node_erase(node->right, age, name);
    } 
    else {
        // If name doesn't match don't delete
        if (strcmp(node->name, name) != 0) {
            return node;
        }

        if (node->left == NULL && node->right == NULL){ // 0 child:
            free(node->name);
            free(node);
            return NULL;
        }
        else if (node->left != NULL && node->right != NULL){ // 2 child:
            Node* predecessor = get_predecessor(node);
            // Swap predecessor with node to delete
            char* new_name = malloc(strlen(predecessor->name) + 1);
            if(new_name == NULL) {
                fprintf(stderr, "Memory allocation failed during node erase\n");
                return node;
            }
            free(node->name);
            node->name = new_name;

            strncpy(node->name, predecessor->name, (strlen(predecessor->name) + 1));
            node->age = predecessor->age;
            // Delete the predecessor node from the left subtree
            node->left = node_erase(node->left, predecessor->age, predecessor->name);
        }
        else if (node->left != NULL){ // 1 left child:
            Node* tmp = node->left;
            free(node->name);
            free(node);
            return tmp;        
        }
        else if (node->right != NULL){ // 1 right child:
            Node* tmp = node->right;
            free(node->name);
            free(node);
            return tmp;
        }
    }
    return node;
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_erase(Tree* tree, int age, char* name) {
    if (tree == NULL) return;
    tree->root = node_erase(tree->root, age, name);
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
    if (node == NULL || name == NULL) return NULL;
    
    if (node->age == age && !strcmp(node->name, name)) {
        return node;
    }

    if (age < node->age) {
        return node_find(node->left, age, name);
    } else {
        return node_find(node->right, age, name);
    }
}

// Tree function: you are allowed to change the contents, but not the method signature
Node* tree_find(Tree* tree, int age, char* name) {
    if (tree == NULL) return NULL;
    return node_find(tree->root, age, name);
}
