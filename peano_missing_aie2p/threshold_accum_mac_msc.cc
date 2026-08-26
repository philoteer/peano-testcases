#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void threshold_accum_mac_msc(const int32_t *__restrict real_input,
                                         const int32_t *__restrict imag_input,
                                         const int32_t *__restrict magnitude,
                                         int32_t *__restrict output) {
  const auto real = aie::load_v<16>(real_input);
  const auto imag = aie::load_v<16>(imag_input);
  const auto mag = aie::load_v<16>(magnitude);

  auto difference = aie::mul<acc64>(real, real);
  difference = aie::mac(difference, imag, imag);
  difference = aie::msc(difference, mag, mag);
  difference = aie::add(difference, INT32_MAX);
  aie::store_v(output, difference.to_vector<int32_t>(31));
}
