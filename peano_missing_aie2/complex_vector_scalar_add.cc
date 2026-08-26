#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void complex_vector_scalar_add(const cint32 *__restrict input,
                                           cint32 *__restrict output) {
  const auto values = aie::load_v<8>(input);
  const cint32 offset = {3, -2};
  aie::store_v(output, aie::add(values, offset));
}
