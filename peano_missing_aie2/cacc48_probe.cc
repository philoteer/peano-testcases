#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

extern "C" void cacc48_probe() {
  aie::accum<cacc48, 16> acc = aie::zeros<cacc48, 16>();
  (void)acc;
}
