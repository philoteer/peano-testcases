#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void unaligned_complex_io(const cint32 *__restrict input,
                                      cint32 *__restrict output) {
  const auto values = aie::load_unaligned_v<16>(input);
  aie::store_unaligned_v(output, values);
}
