#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Complex accumulator extraction used by frame pilot correlation.
extern "C" void cacc64_cast(uint32_t *__restrict output) {
  aie::accum<cacc64, 2> complex_acc;
  const auto real_acc = complex_acc.template cast_to<acc64>();
  const auto words = aie::vector_cast<uint32_t>(real_acc);
  aie::store_v(output, words);
}
