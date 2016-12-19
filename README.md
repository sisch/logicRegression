# logicRegression
## Description
Logic Regression aims to find predictors from logical combinations of original predictors [Ruczinski et al., 2003](http://kooperberg.fhcrc.org/papers/2003logic.pdf)

## How to Build
```bash
mkdir build
cd build
cmake ..
make
```

## How to Run
```bash
./test_logicregression
```

or

```c
#include "optimizer.h"
#include "model.h"
#include "helpers.h"

int main() {
  // data_array_list is a matrix of the binary predictor values
  // response_array is a list of the according response variable values
  // data_array_length is the number of predictor variables
  // data_array_list_length is the number of data points available for fitting.
  simulated_annealing_initialize(int **data_array_list,
                                    uint data_array_length,
                                    uint data_array_list_length,
                                    float *response_array,
                                    float initial_temperature,
                                    float min_temperature,
                                    float coolingrate);
  Model *best_model = start_annealing();
  
  // Output best_model e.g.
  print_subtree(best_model->root_node);
  return 0;
}
```
