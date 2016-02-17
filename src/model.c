//
// Created by schliesky on 2/17/16.
//

#include <stdlib.h>
#include "model.h"

Model *new_model(){
    Model *model1 = (Model*)malloc(sizeof(Model));
    model1->first_tree = create_new_tree();
    model1->last_tree = model1->first_tree;
    return model1;
}