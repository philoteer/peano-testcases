#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

namespace {
constexpr unsigned kFftSize = 64;
alignas(aie::vector_decl_align) static cint16 twiddles[kFftSize] = {};
alignas(aie::vector_decl_align) static cint32 bins[kFftSize] = {};
}

// The r4 stage is the primitive used by the repository's 64-point FFTs.
extern "C" void fft_r4_stage(const cint16 *__restrict input,
                              cint32 *__restrict output) {
  aie::fft_dit_r4_stage<16>(input, twiddles, twiddles, twiddles,
                            kFftSize, 15, 15, false, bins);
  aie::store_v(output, aie::load_v<16>(bins));
}
