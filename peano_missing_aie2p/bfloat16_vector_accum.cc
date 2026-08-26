#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Control case based on the scalar bfloat16 kernels in cpp_bfloat16*.
extern "C" void bfloat16_vector_accum(const bfloat16 *__restrict input,
                                       bfloat16 *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const bfloat16 factor = (bfloat16)2.0f;
  const auto result = aie::mul<accfloat>(values, factor);
  aie::store_v(output, result.template to_vector<bfloat16>(0));
}
