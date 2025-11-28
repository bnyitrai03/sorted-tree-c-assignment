#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "tree.h"

// You are allowed to change anything about this function to fix it
int main() {
    char commandBuffer[64] = {};
    Tree *tree = tree_create();
    if (tree == NULL){
        return 1;
    }

    for(;;) {
        if (fgets(commandBuffer, sizeof(commandBuffer), stdin) == NULL) break;
        char *newline = strchr(commandBuffer, '\n');

        if (newline) {
            *newline = '\0';
        } else {
            // Clear remaining input if line is longer than buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        if (commandBuffer[0] == 'q') break;

        tree = handleString(commandBuffer, tree);
    };

    tree_delete(tree);
    return 0;
}

/**
 * Handle a command entered into the program
 *
 * You are allowed to change anything about this function to fix it
 * @param command The command string to handle
 */
Tree* handleString(char command[], Tree *tree){
    switch(command[0]){
        case 'i':
            tree = insert(command, tree);
            break;
        case 'e':
            erase(command, tree);
            break;
        case 'c':
            check(command, tree);
            break;
        case 'p':
            tree_print(tree, 1);
            break;
        case 'x':
            tree_delete(tree);
            return NULL;
        default:
            fprintf(stderr, "Invalid command string: %s\n", command);
            break;
    }

    return tree;
}

// You are allowed to change anything about this function to tix it
Tree* insert(char* command, Tree* tree) {
    int age;
    char name[16] = {};

    if (sscanf(command, "i %d %15s", &age, name) != 2){
        fprintf(stderr, "Failed to parse insert command: not enough parameters filled\n");
        return tree;
    }

    if (tree == NULL){
        tree = tree_create();
        if (tree == NULL) {
            fprintf(stderr, "Memory allocation failed for new tree\n");
            return NULL;
        }
    }
    tree_insert(tree, age, name);

    return tree;
}

// You are allowed to change anything about this function to fix it
void erase(char* command, Tree* tree) {
    if (tree == NULL) return;

    int age;
    char name[16] = {};

    if (sscanf(command, "e %d %15s", &age, name) != 2){
        fprintf(stderr, "Failed to parse erase command: not enough parameters filled\n");
        return;
    }

    tree_erase(tree, age, name);
}

// You are allowed to change anything about this function to fix it
void check(char* command, Tree* tree) {
    int age;
    char name[16] = {};

    if (sscanf(command, "c %d %15s", &age, name) != 2){
        fprintf(stderr, "Failed to parse check command\n");
        return;
    }

    // If tree is NULL or item not found, print "n"
    if (tree == NULL) {
        printf("n\n");
        return;
    }

    Node* result = tree_find(tree, age, name);
    if (result){
        printf("y\n");
    } else {
        printf("n\n");
    }
}
