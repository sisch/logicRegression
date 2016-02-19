// Simon Schliesky
// Last change 2015-09-08
/** @file */
#include <zconf.h>
#include <stdbool.h>

#ifndef LOGICREGRESSION_LOGICTREE_H
#define LOGICREGRESSION_LOGICTREE_H

typedef struct node Node;
typedef struct logicTree LTree;
/**
 * nodeType
 */
typedef enum nodeType {AND, OR, INDEX, INDEX_COMPLEMENT, ONE} nodeType;
/**
 * childPosition
 */
typedef enum childPosition {LEFT, RIGHT} childPosition;
/* node contains the values and boolean operators in a logicTree
 *
 * Besides holding values or boolean connectors, the hierarchy of the logic tree is resembled by having pointers
 * to up to two child elements and one parent element.
 */
struct node {
    nodeType type;          /**< #nodeType identifier*/
    Node *left_child;       /**< pointer to the left child #node */
    Node *right_child;      /**< pointer to the right child #node */
    Node *parent;           /**< pointer to the parent #node */
    uint depth;             /**< The depth of a node is defined as distance to the root node */
    uint node_index;        /**< A unique numeric index within the logicTree */
    uint data_index;        /**< A numeric index denoting the position of input data in the input array. */
    childPosition position; /**< The #childPosition in a logicTree as seen from the parent node */
};
/* logicTree represents a hierarchical binary tree with nodes containing either a data index or a boolean connector
 *
 * A logicTree consists of a pointer to the root_node (state upon initialization -> TRUE),
 * a pointer to the next_tree (in case of multiple trees),
 * and an unsigned integer representing the height of the tree (i.e. max distance to ANY leaf node)
 */
struct logicTree {
    Node *root_node;
    LTree *next_tree;
    uint height;
    int binary_outcome;
};

// Allowed set of moves to alter a tree
/* alternate_leaf replaces a leaf node with a new one
 *
 * With this function you can either change the type of a leaf (INDEX, INDEX_COMPLEMENT, ONE),
 * the data index, or both. This function can technically attach a subtree as well, this leads to
 * undefined behavior, though.
 */
void split_leaf(LTree *tree, uint index, nodeType new_connector, uint new_child_data_index, nodeType new_child_type);
void alternate_leaf(LTree *tree, uint index, Node *new_node); // 3rd parameter could also be a new value of dataIndex only
void alternate_operator(LTree *tree, uint index, nodeType type);
void grow_branch(LTree *tree, uint index, nodeType new_connector, Node *new_child);
void prune_branch(LTree *tree, uint index, childPosition delete_child_at);
void delete_leaf(LTree *tree, uint index);

// Other tree operations
LTree *create_new_tree();
LTree *add_tree(LTree *root_tree);
Node *create_node(Node *parent, nodeType type, uint data_index, childPosition cp);
Node *find_node_by_index(LTree *tree, uint node_index);
void destroy_tree(LTree *tree, bool include_subsequent);
void destroy_node(Node **node);

// arithmetic tree output
int calculate_subtree_outcome(Node *node, int *data_array, uint max_data_index);
void recalculate_indices(LTree *tree, Node *root_node, uint index_of_root);

#endif //LOGICREGRESSION_LOGICTREE_H
