//
//
// test.c
#include <assert.h>
#include <stdbool.h>
#include <logictree.h>
#include <stdio.h>

static void test_tree_struct() {
    size_t treesize = sizeof(LTree);
    assert(sizeof(LTree) == 24);
    printf("\tStruct Size: passed\n");
    assert(create_new_tree() != NULL);
    printf("\tCreate new tree: passed\n");

}
static void test_node_01(){

}

static void test_all_nodes(){
    printf("Testing Node 01\n");
    test_node_01();
}
static void test_trees(){
    printf("Testing Tree 01\n");
    test_tree_struct();
}

int main(){
    test_trees();
    test_all_nodes();
}
