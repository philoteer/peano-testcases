#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Scalar .real/.imag access used by every cbfloat16 conversion and math kernel.
extern "C" void cbfloat16_scalar_fields(const cbfloat16 *__restrict input,
                                         cbfloat16 *__restrict output) {
  cbfloat16 value = input[0];
  value.real = (bfloat16)1.0f;
  value.imag = (bfloat16)(float)value.imag;
  output[0] = value;
}
