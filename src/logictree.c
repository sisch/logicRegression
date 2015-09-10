// Simon Schliesky
// Last change 2015-09-04

#include <stdbool.h>
#include <stdio.h>
#include "logictree.h"
#include "stdlib.h"

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)
bool is_bit_set(uint index, uint position){
    return (index >> position & 0b1) == 0b1;
}

LTree *create_new_tree(){
    LTree *t = malloc(sizeof(LTree));
    t->next_tree = NULL;
    t->root_node = create_node(NULL,ONE, NULL, RIGHT);
    t->root_node->node_index = 1;
    t->height =1;
    return t;
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

Node *create_node(Node *parent, nodeType type, uint data_index, childPosition cp){
    //TODO: adjust tree height when creating node
    Node *n = malloc(sizeof(Node));
    n->left_child = NULL;
    n->right_child = NULL;
    n->type = type;
    n->parent = parent;
    if(parent!=NULL){
        n->node_index = parent->node_index<<1;
        n->depth = n->parent->depth + 1;
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
    }
    free(n);
}

void split_leaf(LTree *tree, uint index, nodeType new_connector, uint new_child_index, nodeType new_child_type){
    Node *cur_node = tree->root_node;
    // Node index in bitwise comparison is 1: right child node; 0: left child node
    for ( uint i = tree->height - 1; i > 0;i--){
        if (is_bit_set(index, i)){
            cur_node = cur_node->right_child;
        }
        else {
            cur_node = cur_node->left_child;
        }
    }

    // At the specified node:
    // Create a copy as right child node
    // Link to new_child as left child
    // switch cur_node type to new_connector
    if (cur_node != NULL) {
        Node *new_child_right = create_node(cur_node, cur_node->type, cur_node->data_index, RIGHT);
        Node *new_child_left = create_node(cur_node, new_child_type, new_child_index, LEFT);
        uint depth = new_child_right->depth;
        tree->height = MAX(depth+1, tree->height);
        cur_node->data_index = NULL;
        cur_node->type = new_connector;
    }
    else{
        fprintf(stderr, "No rootnode available. Create a tree first and pass the correct pointer.");
    }
}