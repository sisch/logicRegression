//
//
// test.c
#include <assert.h>
#include <stdbool.h>
#include <logictree.h>
#include <stdio.h>
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
    Node* B = create_node(A,ONE,2,LEFT);
    Node* C = create_node(A,ONE,3,RIGHT);
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


static void run_all_node_tests(){
    printf("Testing Node 01 :: Node creation\n");
    test_node_creation();
    printf("Testing Node 02 :: Node relations\n");
    test_node_members();
    printf("Testing Node 03 :: Node destruction\n");
    test_node_destruction();

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
