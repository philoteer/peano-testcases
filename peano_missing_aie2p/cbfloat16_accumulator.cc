#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// caccfloat is the accumulator required by complex bfloat16 multiply kernels.
extern "C" void cbfloat16_accumulator(void) {
  aie::accum<caccfloat, 16> result;
  (void)result;
}
