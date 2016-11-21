// Simon Schliesky
// Last change 2015-09-04

#include <stdbool.h>
#include <stdio.h>
#include "logictree.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)
bool is_bit_set(uint number, uint position) {
  return (number >> position & 0b1) == 0b1;
}

LTree *create_new_tree(int **data_array_list, uint max_data_index) {
  LTree *t = malloc(sizeof(LTree));
  t->next_tree = NULL;
  t->root_node = create_node(NULL, ONE, -1, RIGHT);
  t->root_node->node_index = 1;
  t->root_node->base_tree = t;
  t->height = 1;
  t->binary_outcome = 1;
  t->list_of_data_arrays = data_array_list;
  t->max_data_index = max_data_index;
  return t;
}

LTree *clone_tree(LTree *template) {
  LTree *return_tree = create_new_tree(NULL, NULL);
  return_tree->height = template->height;
  return_tree->binary_outcome = template->binary_outcome;
  return_tree->list_of_data_arrays = template->list_of_data_arrays;
  return_tree->max_data_index = template->max_data_index;
  destroy_node(&return_tree->root_node);
  return_tree->root_node = clone_node(template->root_node, NULL);
  if(template->next_tree != NULL) {
    return_tree->next_tree = clone_tree(template->next_tree);
  }
  return return_tree;
}

void destroy_tree(LTree *tree, bool include_subsequent) {
  if (tree != NULL) {
    if (tree->next_tree != NULL) {
      if (include_subsequent == true) {
        destroy_tree(tree->next_tree, true);
        destroy_node(&tree->root_node);
      }
      else {
        //TODO: find a way to link tree->parent->next_tree to tree->next_tree and then delete tree
        // possibility 1: making LTree double linked list
        // possibility 2: looping through number of trees (no problem if limited, like in publication)
      }
    }
  }
  free(tree);
}
LTree *add_tree(LTree *root_tree) {
  LTree *cur_tree = root_tree;
  while (cur_tree->next_tree != NULL) {
    cur_tree = cur_tree->next_tree;
  }
  LTree *new_tree = create_new_tree(root_tree->list_of_data_arrays, root_tree->max_data_index);
  cur_tree->next_tree = new_tree;
  return new_tree;
}

Node *create_node(Node *parent, nodeType type, uint data_index, childPosition cp) {
  //TODO: adjust tree height when creating node
  Node *n = malloc(sizeof(Node));
  n->left_child = NULL;
  n->right_child = NULL;
  n->type = type;
  n->parent = parent;
  n->position = cp;
  if (parent != NULL) {
    n->base_tree = parent->base_tree;
    n->node_index = parent->node_index << 1;
    n->depth = n->parent->depth + 1;
    if (cp == RIGHT) {
      n->node_index += 1;
      //Introduce check that right Child is not overwritten -> UB
      n->parent->right_child = n;
    }
    else if (cp == LEFT) {
      n->parent->left_child = n;
    }
  }
  else {
    n->node_index = 1;
    n->depth = 0;
  }
  n->data_index = data_index;
  return n;
}
Node *clone_node(Node *template, Node *new_parent) {
  Node *return_node = (Node*)malloc(sizeof(Node));
  return_node->base_tree = template->base_tree;
  return_node->data_index = template->data_index;
  return_node->depth = template->depth;
  return_node->node_index = template->node_index;
  return_node->position = template->position;
  return_node->type = template->type;
  if(template->left_child != NULL) {
    return_node->left_child = clone_node(template->left_child, return_node);
  }
  if(template->right_child != NULL) {
    return_node->right_child = clone_node(template->right_child, return_node);
  }
  return_node->parent = new_parent;
  return return_node;
}
void destroy_node(Node **n) {
  if (*n != NULL) {
    if ((*n)->right_child != NULL) {
      destroy_node(&((*n)->right_child));
    }
    if ((*n)->left_child) {
      destroy_node(&((*n)->left_child));
    }
  }
  if ((*n)->parent != NULL) {
    if ((*n)->position == LEFT) {
      (*n)->parent->left_child = NULL;
    }
    else {
      (*n)->parent->right_child = NULL;
    }
  }
  free(*n);
  *n = NULL;
}

void split_leaf(LTree *tree, uint index, nodeType new_connector, uint new_child_data_index, nodeType new_child_type) {
  Node *cur_node = find_node_by_index(tree, index);
  // At the specified node:
  // Create a copy as right child node
  // Link to new_child as left child
  // switch cur_node type to new_connector
  if (cur_node != NULL) {
    Node *new_child_right = create_node(cur_node, cur_node->type, cur_node->data_index, RIGHT);
    create_node(cur_node, new_child_type, new_child_data_index, LEFT);
    uint depth = new_child_right->depth;
    tree->height = MAX(depth + 1, tree->height);
    cur_node->data_index = NULL;
    cur_node->type = new_connector;
  }
  else {
    fprintf(stderr, "No rootnode available. Create a tree first and pass the correct pointer.");
  }
}
void alternate_leaf(LTree *tree, uint index, Node *new_node) {
  //TODO: Check whether new_node is of type leaf
  assert(new_node->parent == NULL && "New leaf is not allowed to be an existing node of any tree");
  new_node->base_tree = tree;
  Node *old_node = find_node_by_index(tree, index);
  new_node->parent = old_node->parent;
  new_node->node_index = index;
  new_node->depth = new_node->parent->depth + 1;
  old_node->parent = NULL;
  if (old_node->position == RIGHT) {
    new_node->parent->right_child = new_node;
    new_node->position = RIGHT;
  }
  else if (old_node->position == LEFT) {
    new_node->parent->left_child = new_node;
    new_node->position = LEFT;
  }
  destroy_node(&old_node);
}
void alternate_operator(LTree *tree, uint index, nodeType type) {
  Node *cur_node = find_node_by_index(tree, index);
  assert(
      (cur_node->type == AND || cur_node->type == OR)
          && (type == AND || type == OR)
          && "Only operator nodes can be altered with this function to another operator type"
  );
  cur_node->type = type;
}
void grow_branch(LTree *tree, uint index, nodeType new_connector, Node *new_child) {
  Node *old_node = find_node_by_index(tree, index);
  Node *new_node = create_node(old_node->parent, new_connector, -1, old_node->position);
  old_node->position = RIGHT;
  new_child->position = LEFT;
  new_node->node_index = new_node->parent->node_index * 2 + 1;
  new_child->node_index = new_node->node_index * 2;
  new_node->depth = new_node->parent->depth + 1;
  new_child->depth = new_node->depth + 1;
  old_node->depth = new_node->depth + 1;
  new_node->left_child = new_child;
  new_child->parent = new_node;
  new_node->right_child = old_node;
  old_node->parent = new_node;

  recalculate_indices(tree, new_node, index);
  // TODO: traverse indices,depths of sub tree
}
void prune_branch(LTree *tree, uint index, childPosition delete_child_at) {
  Node *old_node = find_node_by_index(tree, index);
  Node *new_node = NULL;
  if (delete_child_at == LEFT) {
    new_node = old_node->right_child;
    old_node->right_child = NULL;
    // assert child to delete is a leaf
    assert(old_node->left_child->left_child == NULL);
    assert(old_node->left_child->right_child == NULL);
  }
  else if (delete_child_at == RIGHT) {
    new_node = old_node->left_child;
    old_node->left_child = NULL;
    // assert child to delete is a leaf
    assert(old_node->right_child->left_child == NULL);
    assert(old_node->right_child->right_child == NULL);
  }
  new_node->parent = old_node->parent;
  old_node->parent = NULL;
  if (old_node == tree->root_node) {
    tree->root_node = new_node;
  } else {
    new_node->position = old_node->position;
    if (new_node->position == LEFT) {
      new_node->parent->left_child = new_node;
    }
    if (new_node->position == RIGHT) {
      new_node->parent->right_child = new_node;
    }
  }
  destroy_node(&old_node);
  recalculate_indices(tree, tree->root_node, 1);
}
void delete_leaf(LTree *tree, uint index) {
  Node *leaf_to_delete = find_node_by_index(tree, index);
  assert(leaf_to_delete->left_child == NULL && leaf_to_delete->right_child == NULL);

  Node *leaf_to_keep = NULL;
  if (leaf_to_delete->position == RIGHT) {
    leaf_to_keep = leaf_to_delete->parent->left_child;
    leaf_to_delete->parent->left_child = NULL;
  }
  if (leaf_to_delete->position == LEFT) {
    leaf_to_keep = leaf_to_delete->parent->right_child;
    leaf_to_delete->parent->right_child = NULL;
  }
  if (leaf_to_delete->parent->position == RIGHT) {
    leaf_to_delete->parent->parent->right_child = leaf_to_keep;
  }
  else if (leaf_to_delete->parent->position == LEFT) {
    leaf_to_delete->parent->parent->left_child = leaf_to_keep;
  }
  leaf_to_keep->parent = leaf_to_delete->parent->parent;
  destroy_node(&leaf_to_delete);
  recalculate_indices(tree, tree->root_node, 1);
}
/*
 * The following will not work, as even a function pointer expects parameters.
 * I need decorators but in C
 * Or I don't need decorators and am confused instead
void *rnd_split_leaf(LTree *tree){
  // find random leaf
  Node *leaf = NULL;
  nodeType new_connector_type = NULL;
  uint random_data_index = 0;
  nodeType new_leaf_type = NULL;
  return split_leaf(tree, leaf->node_index, new_connector_type, random_data_index, new_leaf_type);
}
 */
void *rnd_delete_leaf(){}
void *rnd_alternate_operator(){}
void *rnd_grow_branch(){}
void *rnd_prune_branch(){}
void *rnd_alternate_leaf(){}

void *rnd_tree_alteration(){}

Node *find_node_by_index(LTree *tree, uint node_index) {
  uint current_bit_mask = 1;
  for (int i = 1; i < (sizeof(uint) * 8); i++) {
    current_bit_mask *= 2;
  }
  if ((node_index & current_bit_mask) == current_bit_mask) {
    printf(stderr, "highest bit set on node index. Should not happen.");
    return NULL;
  }
  while ((node_index & current_bit_mask) == 0) {
    current_bit_mask >>= 1;
  }
  Node *current_node = tree->root_node;
  current_bit_mask >>= 1; //root_node is the first set bit
  while (current_bit_mask > 0) {
    if ((node_index & current_bit_mask) == current_bit_mask) {
      current_node = current_node->right_child;
    }
    else if ((node_index & current_bit_mask) == 0) {
      current_node = current_node->left_child;
    }
    current_bit_mask >>= 1;
    if (current_node == NULL) {
      return NULL;
    }
  }
  return current_node;
}
void recalculate_indices(LTree *tree, Node *root_node, uint index_of_root) {
  if (root_node != NULL) {
    root_node->node_index = index_of_root;
    if (root_node->parent != NULL) {
      root_node->depth = root_node->parent->depth + 1;
      tree->height = MAX(tree->height, root_node->depth + 1);
    }
    else {
      root_node->depth = 0;
      tree->height = 1;
    }
    if (root_node->left_child != NULL) {
      recalculate_indices(tree, root_node->left_child, index_of_root * 2);
    }
    if (root_node->right_child != NULL) {
      recalculate_indices(tree, root_node->right_child, index_of_root * 2 + 1);
    }
  }
}

int calculate_subtree_outcome(Node *node, uint dataset_id) {
  if (node->type == ONE) {
    return 1;
  }
  else if (node->type == OR) {
    return MAX(calculate_subtree_outcome(node->left_child, dataset_id),
               calculate_subtree_outcome(node->right_child, dataset_id));
  }
  else if (node->type == AND) {
    return MIN(calculate_subtree_outcome(node->left_child, dataset_id),
               calculate_subtree_outcome(node->right_child, dataset_id));
  }
  else if (node->type == INDEX && node->data_index <= node->base_tree->max_data_index) {
    return node->base_tree->list_of_data_arrays[dataset_id][node->data_index];
  }
  else if (node->type == INDEX_COMPLEMENT && node->data_index <= node->base_tree->max_data_index) {
    return (node->base_tree->list_of_data_arrays[dataset_id][node->data_index] + 1) % 2;
  }
  return -1;
}
