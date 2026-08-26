#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Passing complex fixed-point baseline used by magsq_avg_cf.
extern "C" void cint16_components_magsq(const cint16 *__restrict input,
                                          int32_t *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const auto parts = aie::vector_cast<int16_t>(values);
  const auto real = aie::filter_even(parts, 1);
  const auto imag = aie::filter_odd(parts, 1);
  auto magnitude = aie::mul<acc48>(real, real);
  magnitude = aie::mac(magnitude, imag, imag);
  aie::store_v(output, magnitude.to_vector<int32_t>(7));
}
