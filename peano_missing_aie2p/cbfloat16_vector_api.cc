#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Vector load, add, and store used by the cbfloat16 stream kernels.
extern "C" void cbfloat16_vector_api(const cbfloat16 *__restrict input,
                                      cbfloat16 *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const cbfloat16 offset = {(bfloat16)0.5f, (bfloat16)-0.25f};
  aie::store_v(output, aie::add(values, offset));
}
