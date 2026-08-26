#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Scalar cbfloat16 <-> cint16 conversion used by the conversion examples.
extern "C" void cbfloat16_cint16_conversion(const cbfloat16 *__restrict input,
                                             cint16 *__restrict output,
                                             cbfloat16 *__restrict round_trip) {
  cint16 integer_value;
  integer_value.real = (int16_t)((float)input[0].real * 32768.0f);
  integer_value.imag = (int16_t)((float)input[0].imag * 32768.0f);
  output[0] = integer_value;

  cbfloat16 float_value;
  float_value.real = (bfloat16)((float)integer_value.real / 32768.0f);
  float_value.imag = (bfloat16)((float)integer_value.imag / 32768.0f);
  round_trip[0] = float_value;
}
