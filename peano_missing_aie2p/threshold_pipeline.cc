#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Accumulator narrowing, comparison, and scalar selection used by threshold_cf.
extern "C" void threshold_pipeline(const int32_t *__restrict input,
                                    int8_t *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const auto scaled = aie::mul<acc64>(values, int32_t(1202590843))
                          .to_vector<int32_t>(31);
  const auto positive = aie::gt(scaled, int32_t(0));
  aie::store_v(output, aie::select(int8_t(0), int8_t(1), positive));
}
