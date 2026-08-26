#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void complex_vector_scalar_add_cbfloat16(
    const cbfloat16 *__restrict input, cbfloat16 *__restrict output) {
  const auto values = aie::load_v<16>(input);
  cbfloat16 offset;
  offset.real = (bfloat16)0.5f;
  offset.imag = (bfloat16)-0.25f;
  aie::store_v(output, aie::add(values, offset));
}
