//
//
// test.c
#include <assert.h>
#include <stdbool.h>
#include <logictree.h>
#include <stdio.h>
#include <helpers.h>
#include <stdlib.h>

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
}

static void test_node_destruction(){
    Node* A = create_node(NULL,AND,1,-1);
    create_node(A,ONE,2,LEFT);
    create_node(A,ONE,3,RIGHT);

    destroy_node(&A);
    assert(A == NULL);
    printf("\tNode child destruction: passed\n");

}

static void test_tree_struct(){
    assert(sizeof(LTree) == 24);
    printf("\tStruct Size: passed\n");
    assert(create_new_tree() != NULL);
    printf("\tCreate new tree: passed\n");
    assert(sizeof(*create_new_tree()) == 24);
    printf("\tSize tree instance: passed\n");
}

static void test_node_mod_split(LTree *test_tree){
    nodeType newType = ONE;
    split_leaf(test_tree, 1, OR, -1, newType);
    assert(test_tree->height == 2);
    printf("\tTree height updates: passed\n");
    assert(test_tree->root_node->type == OR);
    printf("\tLeaf new Type: passed\n");
    assert(test_tree->root_node->left_child != NULL);
    printf("\tLeaf has Left Child: passed\n");
    assert(test_tree->root_node->right_child != NULL);
    printf("\tLeaf has Right Child: passed\n");
    assert(test_tree->root_node->right_child->type == ONE);
    printf("\tLeaf right Child equals old_node (ONE): passed\n");
    assert(test_tree->root_node->left_child->type == newType);
    printf("\tLeaf left Child type: passed\n");
    split_leaf(test_tree, 2, AND, 5, INDEX);
    split_leaf(test_tree, 3, OR, 2, INDEX_COMPLEMENT);
    assert(find_node_by_index(test_tree, 1) != NULL); //test_tree->root_node);
    printf("\troot node index: passed\n");
    assert(find_node_by_index(test_tree, 3) == test_tree->root_node->right_child);
    printf("\tright child index: passed\n");
    assert(find_node_by_index(test_tree, 4)->type == INDEX);
    printf("\tnode 4 type: passed\n");
    assert(find_node_by_index(test_tree, 6)->type == INDEX_COMPLEMENT);
    printf("\tnode 6 type: passed\n");




}

static void test_node_modification(){
    LTree *test_node = create_new_tree();
    printf(" - Node Mod 01 : Split Leaf\n");
    test_node_mod_split(test_node);
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
static void run_all_tree_tests(){
    printf("Testing Tree 01\n");
    test_tree_struct();
}

int main(){
    run_all_node_tests();
    printf("\n");
    run_all_tree_tests();
    printf("\n");

}
