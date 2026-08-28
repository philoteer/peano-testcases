#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void portable_vector(const int32_t *__restrict input,
                                 int32_t *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const auto doubled = aie::mul<acc64>(values, int32_t(2));
  aie::store_v(output, doubled.to_vector<int32_t>(0));
}
