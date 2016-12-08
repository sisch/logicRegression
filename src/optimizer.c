//
// Created by Simon Schliesky on 30/11/16.
//

#include "optimizer.h"

Solution *clone_solution(Solution *sol);
void free_solution(Solution *sol);

static Solution *current_solution = NULL;
static float temperature = 10000;
static float end_temperature = 1;
static float cooling_rate = 0.997;
static Solution *best_solution = NULL;

Solution *create_solution(int **data_array_list,
                         uint data_array_length,
                         uint data_array_list_length,
                         float *response_array
) {
  Solution *new_solution = malloc(sizeof(Solution));
  new_solution->model = new_model(data_array_list, data_array_length, data_array_list_length,response_array);
  return new_solution;
}
void simulated_annealing_initialize(int **data_array_list,
                                    uint data_array_length,
                                    uint data_array_list_length,
                                    float *response_array,
                                    float initial_temperature,
                                    float min_temperature,
                                    float coolingrate) {
  current_solution = create_solution(data_array_list,data_array_length,data_array_list_length,response_array);
  best_solution = current_solution;
  current_solution->energy = score(current_solution->model);
  temperature = initial_temperature;
  end_temperature = min_temperature;
  // cooling rate is transformed to a temperature decay rate
  cooling_rate = 1 - coolingrate;
  srand(time(NULL));
}

Model *start_annealing() {
  while(temperature >= end_temperature) {
    Solution *new_solution = clone_solution(current_solution);
    modify_solution(new_solution);
    new_solution->energy = score(new_solution->model);
    if(accept(new_solution->energy, current_solution->energy, temperature)) {
      if(new_solution->energy >= best_solution->energy) {
        best_solution = new_solution;
      }
      free_solution(current_solution);
      current_solution = new_solution;
    }
    temperature *= cooling_rate;
  }
  return best_solution->model;
}
void free_solution(Solution *sol) {
  free_model(sol->model);
  free(sol);
}
Solution *clone_solution(Solution *sol) {
  Solution *clone = malloc(sizeof(Solution));
  clone->model = clone_model(sol->model);
  clone->energy = sol->energy;
  return clone;
}

void modify_solution(Solution *sol) {
  //This is only called after cloning solution.
  // So overwriting values downstream should be no problem.
  rnd_model_alteration(sol->model);
}

bool accept(float new_energy, float old_energy, float temperature) {
  if (new_energy>old_energy) return true;

  if(exp((old_energy-new_energy)/temperature) > drand48()) return true;

  return false;
}
