// Simon Schliesky
// Last change 2015-09-04

#include <stdbool.h>
#include "logictree.h"
#include "stdlib.h"

LTree *create_new_tree(){
    LTree *t = malloc(sizeof(LTree));
    t->next_tree = NULL;
    t->root_node = create_node(NULL,ONE, -1, RIGHT);
    t->root_node->node_index = 1;
}

void destroy_tree(LTree *tree) {
    if (tree != NULL) {
        if (tree->next_tree != NULL) {
            destroy_tree(tree->next_tree);
        }
        destroy_node(tree->root_node);
    }
    free(tree);
}

Node *create_node(Node *parent, nodeType type, int data_index, childPosition cp){
    Node *n = malloc(sizeof(Node));
    n->left_child = NULL;
    n->right_child = NULL;
    n->type = type;
    n->parent = parent;
    if(parent!=NULL){
        n->node_index = parent->node_index<<1;
        if(cp == RIGHT){
            n->node_index += 1;
            //Introduce check that right Child is not overwritten -> UB
            n->parent->right_child = n;
        }
        else if(cp == LEFT){
            n->parent->left_child = n;
        }
    }
    else{
        n->node_index = 1;
    }
    n->data_index = data_index;
    return n;
}

void destroy_node(Node *n){
    if(n != NULL){
        if(n->right_child != NULL){
            destroy_node(n->right_child);
        }
        if(n->left_child){
            destroy_node(n->left_child);
        }
        free(n);
    }
}

void split_leaf(LTree *tree, int index, nodeType newConnector, Node *new_child){
    Node *cur_node = tree->root_node;
    //TODO: Find node with node_index index and split in two
    while(true){
        break;
    }
}