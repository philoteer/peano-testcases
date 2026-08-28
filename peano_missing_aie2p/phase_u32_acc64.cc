#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void phase_u32_acc64(const uint32_t *__restrict input,
                                 uint32_t *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const auto product = aie::mul<acc64>(values, uint32_t(12345));
  aie::store_v(output, product.to_vector<uint32_t>(0));
}
