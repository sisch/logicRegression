// Simon Schliesky
// Last change 2015-09-08

#include <zconf.h>

#ifndef LOGICREGRESSION_LOGICTREE_H
#define LOGICREGRESSION_LOGICTREE_H

typedef struct node Node;
typedef struct logicTree LTree;
typedef enum nodeType {AND, OR, INDEX, INDEX_COMPLEMENT, ONE} nodeType;
typedef enum childPosition {LEFT, RIGHT} childPosition;
struct node {
    nodeType type;
    Node *left_child;
    Node *right_child;
    Node *parent;
    uint depth;
    uint node_index;
    uint data_index;
};

struct logicTree {
    Node *root_node;
    LTree *next_tree;
    uint height;
};

// Allowed set of moves to alter a tree
void alternate_leaf(LTree *tree, uint index, Node *new_node); // 3rd parameter could also be a new value of dataIndex only
void alternate_operator(LTree *tree, uint index, nodeType type);
void grow_branch(LTree *tree, uint index, nodeType new_connector, Node *new_child);
void prune_branch(LTree *tree, uint index, childPosition delete_child_at);
void split_leaf(LTree *tree, uint index, nodeType new_connector, uint new_child_index, nodeType new_child_type);
void delete_leaf(LTree *tree, uint index);

// Other tree operations
LTree *create_new_tree();
Node *create_node(Node *parent, nodeType type, uint data_index, childPosition cp);
Node *find_node_by_index(LTree *tree, uint node_index);
void destroy_tree(LTree *tree);
void destroy_node(Node *node);

// arithmetic tree output
int calculate_tree_outcome(LTree *tree, int *data_array, uint max_data_index);
int get_tree_depth(LTree *tree);
int get_number_of_leaves(LTree *tree);


#endif //LOGICREGRESSION_LOGICTREE_H
