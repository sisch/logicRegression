//
// Created by schliesky on 2/17/16.
//

#include <stdlib.h>
#include <string.h>
#include "model.h"

Model *new_model(int **data_array_list, uint data_arr_length) {
  Model *model1 = (Model *) malloc(sizeof(Model));
  model1->first_tree = create_new_tree(data_array_list, data_arr_length - 1);
  model1->last_tree = model1->first_tree;
  model1->number_of_trees = 1;
  model1->coefficient_array = (float *) malloc(sizeof(float) * model1->number_of_trees + 1);
  memset(model1->coefficient_array, 0, sizeof(float) * (model1->number_of_trees + 1));
  model1->data_array = data_array_list;
  model1->data_array_length = data_arr_length;
  return model1;
}

Model *model_add_tree(Model *model1, float coefficient) {
  model1->number_of_trees++;
  float *old_coefficients = model1->coefficient_array;
  model1->coefficient_array = malloc(sizeof(float) * model1->number_of_trees + 1);
  memset(model1->coefficient_array, 0, sizeof(float) * (model1->number_of_trees + 1));
  memcpy(model1->coefficient_array, old_coefficients, sizeof(float) * model1->number_of_trees);
  free(old_coefficients);
  model1->coefficient_array[model1->number_of_trees] = coefficient;
  model1->last_tree->next_tree = add_tree(model1->last_tree);
  model1->last_tree = model1->last_tree->next_tree;
  return model1;
}

float calculate_model(Model *model1) {
  int tree_num = 1;
  float result = model1->coefficient_array[0];
  LTree *cur_tree = model1->first_tree;
  while (tree_num <= model1->number_of_trees) {
    // 1-dimensional data only, for the moment
    result += model1->coefficient_array[tree_num] * cur_tree->binary_outcome;
    tree_num++;
    cur_tree = cur_tree->next_tree;
  }
  return result;
}

