#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

// Scoped rounding and saturation modes used throughout the synchronizers.
extern "C" void scoped_mode_probe(const int16_t *__restrict input,
                                   int16_t *__restrict output) {
  const auto values = aie::load_v<16>(input);

  {
    aie::scoped_mode rounding{aie::rounding_mode::positive_inf};
    aie::scoped_mode saturation{aie::saturation_mode::none};
    aie::store_v(output,
                 aie::mul<acc64>(values, int16_t(3)).to_vector<int16_t>(0));
  }
  {
    aie::scoped_mode rounding{aie::rounding_mode::symmetric_inf};
    aie::scoped_mode saturation{aie::saturation_mode::saturate};
    aie::store_v(output,
                 aie::mul<acc64>(values, int16_t(3)).to_vector<int16_t>(0));
  }
  {
    aie::scoped_mode rounding{aie::rounding_mode::symmetric_floor};
    aie::scoped_mode saturation{aie::saturation_mode::saturate};
    aie::store_v(output,
                 aie::mul<acc64>(values, int16_t(3)).to_vector<int16_t>(0));
  }
}
