#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Scalar cbfloat16 <-> cint32 conversion used by the OFDM format converters.
extern "C" void cbfloat16_cint32_conversion(const cbfloat16 *__restrict input,
                                             cint32 *__restrict output,
                                             cbfloat16 *__restrict round_trip) {
  cint32 integer_value;
  integer_value.real = (int32_t)((float)input[0].real * 65536.0f);
  integer_value.imag = (int32_t)((float)input[0].imag * 65536.0f);
  output[0] = integer_value;

  cbfloat16 float_value;
  float_value.real = (bfloat16)((float)integer_value.real / 65536.0f);
  float_value.imag = (bfloat16)((float)integer_value.imag / 65536.0f);
  round_trip[0] = float_value;
}
