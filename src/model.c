//
// Created by schliesky on 2/17/16.
//

#include <stdlib.h>
#include <string.h>
#include "model.h"

Model *new_model(int **data_array_list, uint data_arr_length, uint data_array_list_length, float *resp_array) {
  Model *model1 = (Model *) malloc(sizeof(Model));
  model1->first_tree = create_new_tree(data_array_list, data_arr_length - 1);
  model1->last_tree = model1->first_tree;
  model1->number_of_trees = 1;
  model1->coefficient_array = (float *) malloc(sizeof(float) * model1->number_of_trees + 1);
  memset(model1->coefficient_array, 0, sizeof(float) * (model1->number_of_trees + 1));
  model1->data_array = data_array_list;
  model1->data_array_length = data_arr_length;
  model1->data_array_list_length = data_array_list_length;
  model1->response_array = resp_array;
  return model1;
}

Model *clone_model(Model *template) {
  Model *model_copy = (Model *) malloc(sizeof(Model));
  model_copy->data_array_length = template->data_array_length;
  model_copy->data_array_list_length= template->data_array_list_length;
  model_copy->number_of_trees = template->number_of_trees;
  model_copy->coefficient_array = (float *)malloc(sizeof(float)*model_copy->number_of_trees + 1);
  memcpy(model_copy->coefficient_array,template->coefficient_array,sizeof(float)*model_copy->number_of_trees + 1);
  model_copy->first_tree = clone_tree(template->first_tree);
  LTree *currentTree = model_copy->first_tree;
  while(currentTree->next_tree != NULL){
    currentTree = currentTree->next_tree;
  }
  model_copy->last_tree = currentTree;
  //use same data array, as it does not change
  model_copy->data_array = template->data_array;
  return model_copy;
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

void calculate_coefficients(Model *model1) {
  // Moore Penrose Pseudoinverse
  // X_ij = L_j(x_i)
  // M = (X^T*X)^-1 * X^T
  // betas for least squares
  // beta = M * y

  //TODO: call GSL or MESCHACH or BLAS functions to calculate betas with Moore-Penrose-approach
  
}

float *calculate_outcome(Model *model1) {
  float *result = malloc(sizeof(float) * model1->data_array_list_length);
  for(int i = 0; i<model1->data_array_list_length;i++) {
    result[i] = model1->coefficient_array[0];
  }
  for(uint dataset_id=0;dataset_id<model1->data_array_list_length;dataset_id++) {
    LTree *cur_tree = model1->first_tree;
    int tree_num = 1;
    while (tree_num <= model1->number_of_trees) {
      // 1-dimensional data only, for the moment
      int tree_outcome = calculate_subtree_outcome(cur_tree->root_node, dataset_id);
      result[dataset_id] += model1->coefficient_array[tree_num] * tree_outcome;
      tree_num++;
      cur_tree = cur_tree->next_tree;
    }
  }
  return result;
}

float score(Model *model1) {
  float sum_of_squared_errors = 0;
  calculate_coefficients(model1);
  float *result = calculate_outcome(model1);
  for (int i = 0; i < model1->data_array_length; i++) {
    float difference = model1->response_array[i] - result[i];
    sum_of_squared_errors += (difference*difference);
  }
  return sum_of_squared_errors;
}
void free_model(Model *model1) {
  destroy_tree(model1->first_tree, true);
  free(model1->coefficient_array);
  free(model1->first_tree);
  free(model1->last_tree);
  free(model1);
}

void rnd_model_alteration(Model *model1) {
  LTree *cur_tree = model1->first_tree;
  while(cur_tree != NULL) {
    rnd_tree_alteration(cur_tree);
    cur_tree = cur_tree->next_tree;
  }
}