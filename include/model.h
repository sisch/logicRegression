//
// Created by schliesky on 2/17/16.
//


#include "logictree.h"
#include <cblas.h>

#ifndef LOGICREGRESSION_MODEL_H
#define LOGICREGRESSION_MODEL_H



typedef struct model Model;
struct model {
  int number_of_trees;
  LTree *first_tree;
  LTree *last_tree;
  float *coefficient_array;
  int **data_array;
  float *response_array;
  uint data_array_length;
  uint data_array_list_length;
};

Model *new_model(int **data_array_list, uint data_arr_length, uint data_array_list_length, float *resp_array);
Model *clone_model(Model *template);
Model *model_add_tree(Model *model1, float coefficient);
void calculate_coefficients(Model *model1);
float *calculate_outcome(Model *model1);
float score(Model *model1);
void free_model(Model *model1);
void rnd_model_alteration(Model *model1);
#endif //LOGICREGRESSION_MODEL_H
