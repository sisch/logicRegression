//
//
// test.c
#include <assert.h>
#include <stdbool.h>
#include "logictree.h"
#include <stdio.h>
#include "helpers.h"
#include <stdlib.h>

LTree *default_tree(){
    LTree *new_tree = create_new_tree();
    split_leaf(new_tree, 1, OR, -1, ONE);
    split_leaf(new_tree, 2, AND, 5, INDEX);
    split_leaf(new_tree, 3, OR, 2, INDEX_COMPLEMENT);
    return new_tree;
}

static void test_node_creation(){
    assert(sizeof(Node) == 48);
    printf("\tStruct Size: passed\n");
    assert(create_node(NULL,-1,-1,-1) != NULL);
    printf("\tNew node: passed\n");
    Node* testnode = create_node(NULL,ONE,-1,LEFT);
    assert(testnode->data_index == -1);
    printf("\tData index -1: passed\n");
    assert(testnode->depth == 0);
    printf("\tDepth 0: passed\n");
    assert(testnode->left_child == NULL);
    printf("\tNo left child: passed\n");
    assert(testnode->right_child == NULL);
    printf("\tNo right child: passed\n");
    assert(testnode->node_index == 1);
    printf("\tNode index 1: passed\n");
    assert(testnode->parent == NULL);
    printf("\tNo parent: passed\n");
    assert(testnode->position == LEFT);
    printf("\tNode position LEFT: passed\n");
    assert(testnode->type == ONE);
    printf("\tNode type ONE: passed\n");
}

static void test_node_members(){
    Node* A = create_node(NULL,AND,1,-1);
    Node* B = create_node(A,ONE,2,LEFT);
    Node* C = create_node(A,ONE,3,RIGHT);
    assert(A->left_child->parent == A);
    printf("\tNode relation left child's parent: passed\n");
    assert(A->left_child->position == LEFT);
    printf("\tNode relation left child's position: passed\n");
    assert(A->right_child->parent == A);
    printf("\tNode relation right child's parent: passed\n");
    assert(A->right_child->position == RIGHT);
    printf("\tNode relation right child's position: passed\n");
    assert(A->right_child == C);
    printf("\tNode relation right child created right: passed\n");
    assert(A->left_child == B);
    printf("\tNode relation left child created left: passed\n");
}

static void test_node_destruction(){
    Node* A = create_node(NULL,AND,1,-1);
    create_node(A,ONE,2,LEFT);
    create_node(A,ONE,3,RIGHT);

    destroy_node(&A);
    assert(A == NULL);
    printf("\tNode child destruction: passed\n");

}

static void test_node_mod_split(LTree *test_tree){
    split_leaf(test_tree, 1, OR, -1, ONE);
    assert(test_tree->height == 2);
    printf("\tTree height updates: passed\n");
    split_leaf(test_tree, 2, AND, 5, INDEX);
    split_leaf(test_tree, 3, OR, 2, INDEX_COMPLEMENT);
    assert(test_tree->root_node->type == OR);
    printf("\tLeaf new Type: passed\n");
    assert(test_tree->root_node->left_child != NULL);
    printf("\tLeaf has Left Child: passed\n");
    assert(test_tree->root_node->right_child != NULL);
    printf("\tLeaf has Right Child: passed\n");
    assert(test_tree->root_node->right_child->right_child->type == ONE);
    printf("\tLeaf right Child equals old_node (ONE): passed\n");
    assert(test_tree->root_node->left_child->type == AND);
    printf("\tLeaf left Child type: passed\n");
    assert(find_node_by_index(test_tree, 1) != NULL);
    printf("\troot node index: passed\n");
    assert(find_node_by_index(test_tree, 3) == test_tree->root_node->right_child);
    printf("\tright child index: passed\n");
    assert(find_node_by_index(test_tree, 4)->type == INDEX);
    printf("\tnode 4 type: passed\n");
    assert(find_node_by_index(test_tree, 6)->type == INDEX_COMPLEMENT);
    printf("\tnode 6 type: passed\n");
    assert(find_node_by_index(test_tree, 7)->type == ONE);
    printf("\tnode 7 type: passed\n");
}

static void test_node_mod_alternate(LTree *test_tree){
    nodeType newType = ONE;
    split_leaf(test_tree, 1, OR, -1, newType);
    split_leaf(test_tree, 2, AND, 5, INDEX);
    split_leaf(test_tree, 3, OR, 2, INDEX_COMPLEMENT);
    assert(find_node_by_index(test_tree,6)->right_child == NULL && find_node_by_index(test_tree,6)->left_child == NULL);
    printf("\ttest node is leaf: passed\n");
    assert(find_node_by_index(test_tree,6)->type == INDEX_COMPLEMENT);
    printf("\ttest leaf type before alternate IC: passed\n");
    Node *test_node = create_node(NULL,newType,-1,-1);

    alternate_leaf(test_tree,6,test_node);
    assert(find_node_by_index(test_tree,6)->parent == find_node_by_index(test_tree,3));
    printf("\ttest leaf parent: passed\n");
    assert(find_node_by_index(test_tree,3)->left_child == find_node_by_index(test_tree,6));
    printf("\ttest leaf leftchild of parent: passed\n");
    assert(find_node_by_index(test_tree,6)->position == LEFT);
    printf("\ttest leaf child position: passed\n");

    newType = ONE;
    alternate_leaf(test_tree,6,create_node(NULL,newType,-1,-1));
    assert(find_node_by_index(test_tree,6)->type == newType);
    printf("\tchange test leaf type to ONE: passed\n");

    newType = INDEX;
    alternate_leaf(test_tree,6,create_node(NULL,newType,-1,-1));
    assert(find_node_by_index(test_tree,6)->type == newType);
    printf("\tchange test leaf type to INDEX: passed\n");

    newType = INDEX_COMPLEMENT;
    alternate_leaf(test_tree,6,create_node(NULL,newType,-1,-1));
    assert(find_node_by_index(test_tree,6)->type == newType);
    printf("\tchange test leaf type to IC: passed\n");

    assert(find_node_by_index(test_tree,6)->node_index == 6);
    printf("\tnew leaf node index: passed\n");
    assert(find_node_by_index(test_tree,6)->depth == 2);
    printf("\tnew leaf depth: passed\n");
}

static void test_node_mod_alternate2(LTree *test_tree){
    nodeType newType = ONE;
    split_leaf(test_tree, 1, OR, -1, newType);
    split_leaf(test_tree, 2, AND, 5, INDEX);
    split_leaf(test_tree, 3, OR, 2, INDEX_COMPLEMENT);
    assert(find_node_by_index(test_tree,3)->type == OR);
    printf("\ttest node initial type OR: passed\n");
    alternate_operator(test_tree, 3, AND);
    assert(find_node_by_index(test_tree,3)->type == AND);
    printf("\ttest node type AND: passed\n");
}

static void test_node_grow_branch(LTree *test_tree){
    Node *new_node = create_node(NULL, INDEX, 3, NULL);
    grow_branch(test_tree, 3, AND, new_node);
    assert(test_tree->root_node->right_child->type == AND);
    printf("\tgrow node new type: passed\n");
    assert(test_tree->root_node->right_child->node_index == 3);
    printf("\tgrow node node index: passed\n");

}

static void test_node_modification(){
    LTree *test_tree = create_new_tree();
    printf(" - Node Mod 01 : Split Leaf\n");
    test_node_mod_split(test_tree);
    printf(" - Node Mod 02 : Alternate Leaf\n");
    destroy_tree(test_tree);
    test_tree = default_tree();
    test_node_mod_alternate(test_tree);
    printf(" - Node Mod 03 : Alternate Operator\n");
    destroy_tree(test_tree);
    test_tree = default_tree();
    test_node_mod_alternate2(test_tree);
    printf(" - Node Mod 04 : Grow Branch\n");
    destroy_tree(test_tree);
    test_tree = default_tree();
    test_node_grow_branch(test_tree);
}

static void run_all_node_tests(){
    printf("Testing Node 01 :: Node creation\n");
    test_node_creation();
    printf("Testing Node 02 :: Node relations\n");
    test_node_members();
    printf("Testing Node 03 :: Node destruction\n");
    test_node_destruction();
    printf("Testing Node 04 :: Modification\n");
    test_node_modification();

}

/*
 * Tree Tests
 *
 */
static void test_tree_struct(){
    assert(sizeof(LTree) == 24);
    printf("\tStruct Size: passed\n");
    assert(create_new_tree() != NULL);
    printf("\tCreate new tree: passed\n");
    assert(sizeof(*create_new_tree()) == 24);
    printf("\tSize tree instance: passed\n");
}

static void run_all_tree_tests(){
    printf("Testing Tree 01\n");
    test_tree_struct();
}


/*
 * main test invocation
 */
int main(){
    run_all_tree_tests();
    printf("\n");
    run_all_node_tests();
    printf("\n");

}
