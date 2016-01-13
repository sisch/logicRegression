//
// Created by Simon Schliesky on 10/09/15.
//

#include <stdio.h>
#include "helpers.h"
#include "logictree.h"

void print_tree(Node *rootNode){
    if (rootNode != NULL) {
        if (rootNode->right_child != NULL)
            print_tree(rootNode->right_child);
        if (rootNode->left_child != NULL)
            print_tree(rootNode->left_child);
        printf("%d(%d):l %p, r %p, %d => %d\n",
               rootNode->node_index,
               rootNode->type,
               rootNode->left_child,
               rootNode->right_child,
               rootNode->depth,
               rootNode->data_index
        );
    }
}