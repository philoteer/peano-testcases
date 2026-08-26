#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void sliding_cacc64(const cint16 *__restrict coefficients,
                                const cint16 *__restrict input,
                                cint32 *__restrict output) {
  auto correlations = aie::sliding_mul<16, 16, 1, 1, 1, cacc64>(
      aie::load_v<16>(coefficients), 0,
      aie::load_unaligned_v<32>(input), 0);

  for (int offset = 16; offset < 32; offset += 16) {
    correlations = aie::sliding_mac<16, 16>(
        correlations, aie::load_v<16>(coefficients + offset), 0,
        aie::load_unaligned_v<32>(input + offset), 0);
  }

  aie::store_v(output, correlations.template to_vector<cint32>(8));
}

extern "C" void sliding_cacc64_small(const cint32 *__restrict previous,
                                      const cint32 *__restrict current) {
  const auto correlation = aie::sliding_mul<2, 4, 1, 1, 1, cacc64>(
      aie::op_conj(aie::load_v<4>(previous)), 0, aie::load_v<4>(current), 0);
  (void)correlation;
}
