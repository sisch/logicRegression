//
// Created by schliesky on 2/17/16.
//

#include <stdlib.h>
#include <string.h>
#include "model.h"

Model *new_model(int *data_arr, int data_arr_length) {
    Model *model1 = (Model *)malloc(sizeof(Model));
    model1->first_tree = create_new_tree();
    model1->last_tree = model1->first_tree;
    model1->number_of_trees = 1;
    model1->coefficient_array = (float *)malloc(sizeof(float)*model1->number_of_trees+1);
    memset(model1->coefficient_array, 0, (size_t)model1->number_of_trees+1);
    model1->data_array = data_arr;
    model1->data_array_length = data_arr_length;
    return model1;
}

float calculate_model(Model *model1) {
    int tree_num = 1;
    float result = model1->coefficient_array[0];
    LTree *cur_tree = model1->first_tree;
    while(cur_tree != NULL) {
        // 1-dimensional data only, for the moment
        result += model1->coefficient_array[tree_num]*calculate_subtree_outcome(cur_tree->root_node, model1->data_array, (uint)model1->data_array_length);
        tree_num++;
        cur_tree = cur_tree->next_tree;
    }
    return result;
}