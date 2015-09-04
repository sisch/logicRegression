// Simon Schliesky
// Last change 2015-09-04

#ifndef LOGICREGRESSION_LOGICTREE_H
#define LOGICREGRESSION_LOGICTREE_H

typedef struct node Node;
typedef struct logicTree Tree;
typedef enum nodeType nodeType;
typedef enum childPosition childPosition;

enum nodeType {AND, OR, INDEX, INDEX_COMPLEMENT};
enum childPosition {LEFT, RIGHT};

struct node {
    nodeType type;
    Node *leftChild;
    Node *rightChild;
    int nodeIndex;
    int dataIndex;
};

struct logicTree {
    Node *rootNode;
    int depth;
};

// Allowed set of moves to alter a tree
void alternate_leaf(Tree *tree, int index, Node *new_node); // 3rd parameter could also be a new value of dataIndex only
void alternate_operator(Tree *tree, int index, nodeType type);
void grow_branch(Tree *tree, int index, nodeType new_connector, Node *new_child);
void prune_branch(Tree *tree, int index, childPosition delete_child_at);
void split_leaf(Tree *tree, int index, nodeType newConnector, Node *new_child);
void delete_leaf(Tree *tree, int index);

// Other possible moves
Tree *create_new_tree();

#endif //LOGICREGRESSION_LOGICTREE_H
