#include <math.h>

// Scalar math calls used by the frequency-source and complex-argument kernels.
extern "C" void libm_float_functions(float input, float *output) {
  output[0] = atan2f(input, -input);
  output[1] = cosf(input);
  output[2] = sinf(input);
  output[3] = floorf(input);
}
