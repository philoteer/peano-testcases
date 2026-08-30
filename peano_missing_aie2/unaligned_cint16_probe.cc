#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void unaligned_cint16_probe(const cint16 *__restrict in,
                                       cint16 *__restrict out) {
  const auto v = aie::load_unaligned_v<16>(in);
  aie::store_unaligned_v(out, v);
}
