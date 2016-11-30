//
// Created by Simon Schliesky on 30/11/16.
//

#include <stdbool.h>
#include "model.h"
#include <math.h>
#include <time.h>
#ifndef LOGICREGRESSION_OPTIMIZER_H
#define LOGICREGRESSION_OPTIMIZER_H

typedef struct solution Solution;
struct solution {
  Model *model;
  float energy;
};


void simulated_annealing_initialize(int **data_array_list,
                                    uint data_array_length,
                                    uint data_array_list_length,
                                    float *response_array,
                                    float initial_temperature,
                                    float end_temperature,
                                    float cooling_rate);

// returns model with best solution.
Model *start_annealing();
void modify_solution(Solution *sol);
void free_solution(Solution *sol);
Solution *clone_solution(Solution *sol);
bool accept(float new_energy, float old_energy, float temperature);

#endif //LOGICREGRESSION_OPTIMIZER_H
