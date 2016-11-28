//
// Created by Simon Schliesky on 10/09/15.
//

#include <stdio.h>
#include <math.h>
#include "helpers.h"
static const float EPSILON = 0.0000001;
void print_tree(LTree *tree) {
  print_subtree(tree->root_node);
}
void print_subtree(Node *rootNode) {
  if (rootNode != NULL) {
    if (rootNode->right_child != NULL)
      print_subtree(rootNode->right_child);
    if (rootNode->left_child != NULL)
      print_subtree(rootNode->left_child);
    printf("%d(%d)\tl %p\tr %p\t%d\t%d\n",
           rootNode->node_index,
           rootNode->type,
           rootNode->left_child,
           rootNode->right_child,
           rootNode->depth,
           rootNode->data_index
    );
  }
}
bool floats_are_same(float a, float b) {
  return fabs(a - b) < EPSILON;
}
