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
    int *coefficient_array;
};

Model *new_model();


#endif //LOGICREGRESSION_MODEL_H
