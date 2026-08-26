#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void complex_scalar_ops(const cint32 *__restrict input,
                                    cint32 *__restrict output) {
  const cint32 first = input[0];
  const cint32 second = input[1];

  output[0] = -first;
  output[1] = int32_t(3) * first;
  output[2] = first + second;
}
