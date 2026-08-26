#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Vector plus complex scalar is used by the autocorrelation prefix sum.
extern "C" void complex_vector_scalar_add(const cint32 *__restrict input,
                                           cint32 *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const cint32 offset = {3, -2};
  aie::store_v(output, aie::add(values, offset));
}
