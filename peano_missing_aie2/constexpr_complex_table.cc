#include <stdint.h>

#include <aie_api/aie.hpp>
#include <aie_api/aie_types.hpp>

alignas(32) static constexpr cint16 coefficient_table[16] = {
    {22721, 0},   {-745, 17496}, {5780, 16163},  {14080, -12039},
    {3070, -4055}, {8698, 12753}, {-16741, 8023}, {-5572, 15439},
    {14184, 3765}, {7756, -593},  {144, 16723},   {-19893, 6889},
    {3559, 8511},  {8531, 2173},  {-3269, -23362}, {17339, 595},
};

extern "C" void constexpr_complex_table(cint16 *__restrict output) {
  // Use scalar copy to isolate the `static constexpr` failure from the
  // complex `load_v` probe (kept in complex_vector_scalar_add.cc).
  for (int i = 0; i < 16; ++i) output[i] = coefficient_table[i];
}
