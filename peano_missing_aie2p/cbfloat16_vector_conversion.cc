#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// cint16 -> cbfloat16 conversion used by the vector frequency source.
extern "C" void cbfloat16_vector_conversion(const cint16 *__restrict input,
                                             cbfloat16 *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const auto converted = aie::to_float<cbfloat16>(values, 15);
  aie::store_v(output, converted);
}
