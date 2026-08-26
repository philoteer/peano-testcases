#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Component extraction used by magnitude and threshold kernels.
extern "C" void complex_vector_components(const cint32 *__restrict input,
                                           int32_t *__restrict real_output,
                                           int32_t *__restrict imag_output) {
  const auto values = aie::load_v<16>(input);
  const auto parts = aie::vector_cast<int32_t>(values);
  aie::store_v(real_output, aie::filter_even(parts, 1));
  aie::store_v(imag_output, aie::filter_odd(parts, 1));
}
