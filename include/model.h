//
// Created by schliesky on 2/17/16.
//

#ifndef LOGICREGRESSION_MODEL_H
#define LOGICREGRESSION_MODEL_H

#include "logictree.h"

typedef struct model Model;
struct model {
  int number_of_trees;
  LTree *first_tree;
  LTree *last_tree;
  float *coefficient_array;
  int **data_array;
  int data_array_length;
};

Model *new_model(int **data_array_list, uint data_arr_length);
Model *model_add_tree(Model *model1, float coefficient);
float calculate_model(Model *model1);

#endif //LOGICREGRESSION_MODEL_H
