// Simon Schliesky
// Last change 2015-09-08

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "main.h"
#include "logictree.h"
#include "helpers.h"


int main() {
  printf("Hello World!\n");
  nodeType nt = INDEX;
  printf("%d\n\n", nt);
  testTrees();
  return 0;
}

void testTrees() {
  LTree *list_of_trees = NULL;
  list_of_trees = create_new_tree();
  //list_of_trees->next_tree = create_new_tree();
  split_leaf(list_of_trees, 0b1, AND, 4, INDEX_COMPLEMENT);
  split_leaf(list_of_trees, 0b10, OR, 1, INDEX);

  assert(list_of_trees->root_node->type == AND);
  assert(list_of_trees->root_node->right_child->type == OR);
  assert(list_of_trees->root_node->left_child->data_index == 4);

  print_tree(list_of_trees);
  destroy_tree(list_of_trees, true);
}