#include <math.h>
#include <stdint.h>

#include <aie_api/aie.hpp>

extern "C" void libm_float_functions(float input, float *__restrict output) {
  output[0] = atan2f(input, -input);
  output[1] = cosf(input);
  output[2] = sinf(input);
  output[3] = floorf(input);
}
