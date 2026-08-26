# Peano XDNA2 Missing-Feature Probes

These are compile-only `aie2p` probes for Peano. They are intentionally kept
separate from `peano_missing`, because this directory targets XDNA2 with
`--target=aie2p-none-unknown-elf` and has no XChessCC path. XChessCC is not
invoked or detected here while its local aie2p installation is incomplete.

Each source isolates one construct used by the repository's existing kernels.
The expected result with the current Peano checkout is a mixture of passing
controls and failures. A failure log is a useful porting checklist item, not a
runtime test failure.

## Cases

| Source | Existing-kernel construct covered |
| --- | --- |
| `portable_vector.cc` | Integer vector multiply and accumulator narrowing control case |
| `bfloat16_vector_accum.cc` | Real bfloat16 vector multiply and `accfloat` narrowing |
| `cint16_vector_accum.cc` | Complex fixed-point vector multiply and `cacc48` narrowing |
| `cint16_components_magsq.cc` | Passing complex fixed-point load, component extraction, and magnitude square |
| `complex_vector_components.cc` | Complex vector cast and even/odd component extraction |
| `phase_u32_acc64.cc` | Unsigned phase vector multiply with `acc64` |
| `unaligned_complex_io.cc` | Unaligned complex vector load and store |
| `complex_scalar_ops.cc` | Scalar `cint32` negation, multiply, and addition |
| `complex_vector_scalar_add.cc` | `aie::add(vector<cint32>, cint32)` |
| `scoped_mode.cc` | Scoped rounding and saturation modes |
| `constexpr_complex_table.cc` | `static constexpr cint16` coefficient tables |
| `sliding_cacc64.cc` | Full and small `sliding_mul`/`sliding_mac` with `cacc64` |
| `cacc64_cast.cc` | Complex accumulator to real accumulator and vector cast |
| `threshold_pipeline.cc` | `acc64` narrowing, comparison, and scalar selection |
| `threshold_accum_mac_msc.cc` | Threshold `acc64` multiply, MAC, MSC, and add sequence |
| `fft_r4_stage.cc` | 64-point radix-4 FFT stage primitive |
| `libm_float_functions.cc` | Scalar `atan2f`, `cosf`, `sinf`, and `floorf` |

The FFT, complex-vector, unaligned-I/O, and sliding cases are deliberately small
enough to expose current XDNA2 backend failures without the unrelated state and
metadata code from the complete kernels. The two threshold probes split the
arithmetic path into controls; the full threshold kernel currently reaches the
backend failure covered by `complex_vector_components.cc`.

## Usage

From this directory, the default `aie2p` target runs every Peano probe and
continues after each failure:

```sh
make
```

The shortcut works from any directory:

```sh
bash /path/to/aie-kernel-src/peano_missing_aie2p/run_tests.sh
```

`make clean` removes generated objects and logs. Failed compiler output is
retained in `build/logs/peano/`, and the command ends with a colored
total/pass/fail/skip summary. A missing Peano installation is reported as a
skip and returns status `2` because no probes were run.

Set `PEANO_INSTALL_DIR` or `MLIR_AIE_DIR` when the local installations are
outside the repository's usual environment.
