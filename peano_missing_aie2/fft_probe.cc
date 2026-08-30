#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

alignas(32) static int16_t tw[64] = {};
alignas(32) static int32_t buf[64] = {};

extern "C" void fft_probe(const int16_t *__restrict in,
                          int32_t *__restrict out) {
  (void)out;
  aie::fft_dit_r4_stage<16>(in, tw, tw, tw, 64, 15, 15, false, buf);
}
