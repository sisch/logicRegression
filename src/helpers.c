//
// Created by Simon Schliesky on 10/09/15.
//

#include <stdio.h>
#include "helpers.h"
#include "logictree.h"

void print_tree(LTree *tree){
    print_node(tree->root_node);
}

void print_node(Node *n){
    if (n != NULL) {
        if (n->right_child != NULL)
            print_node(n->right_child);
        if (n->left_child != NULL)
            print_node(n->left_child);
        printf("%d(%d):l %p, r %p, %d => %d\n", n->node_index,n->type, n->left_child, n->right_child, n->depth, n->data_index);
    }
}