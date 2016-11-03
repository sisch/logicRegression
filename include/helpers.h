//
// Created by Simon Schliesky on 10/09/15.
//
#include "logictree.h"
#include <math.h>
#include <stdbool.h>
#ifndef LOGICREGRESSION_HELPERS_H
#define LOGICREGRESSION_HELPERS_H
//static const float EPSILON = 0.000000001f;
void print_tree(LTree *);
void print_subtree(Node *);
bool floats_are_same(float a, float b);
#endif //LOGICREGRESSION_HELPERS_H
