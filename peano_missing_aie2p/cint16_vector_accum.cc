#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Complex fixed-point multiply used by the synchronizer oscillators.
extern "C" void cint16_vector_accum(const cint16 *__restrict input,
                                     const cint16 *__restrict factor,
                                     cint32 *__restrict output) {
  const auto values = aie::load_v<16>(input);
  const auto factors = aie::load_v<16>(factor);
  const auto result = aie::mul<cacc48>(values, factors);
  aie::store_v(output, result.template to_vector<cint32>(15));
}
