# Peano Missing-Feature Probes

These are compile-only `aie2` probes extracted from constructs used by the
AI Engine kernels in this repository. They deliberately have no MLIR graph,
runtime, or host-side test so that a compiler error identifies one API or
language feature.

The default target tests Peano. The `xchesscc` target is an explicit
compatibility check, and the `check` target runs both compilers. The Peano
target is expected to fail with the current Peano installation and should
compile once the corresponding implementation gaps are fixed.

`portable_vector.cc` is a control case. It uses only ordinary vector and
accumulator operations and is expected to compile with both compilers. If it
fails, investigate the build configuration before investigating the missing
features.

## Cases

| Source | Existing-kernel construct covered |
| --- | --- |
| `portable_vector.cc` | Control case using ordinary `int32` vector multiply and narrowing |
| `complex_scalar_ops.cc` | Unary negation, scalar multiplication, and addition of `cint32` values |
| `complex_vector_scalar_add.cc` | `aie::load_v` for complex `cint32` vectors (single `load_v` probe; other complex loads removed) |
| `cacc64_cast.cc` | `cacc64` to real `acc64` extraction and vector casting |
| `cacc48_probe.cc` | `cacc48` 48-bit complex accumulator (`aie::zeros<cacc48>`) |
| `unaligned_cint16_probe.cc` | `aie::load_unaligned_v`/`store_unaligned_v` for `cint16`  |
| `constexpr_complex_table.cc` | `static constexpr cint16` tables used for FIR/FFT coefficients (scalar copy, no `load_v`) |
| `libm_float_functions.cc` | `atan2f`, `cosf`, `sinf`, and `floorf` in scalar kernel code |

## Usage

From this directory, the default target runs Peano only and continues through
every source after a failure:

```sh
make
```

Running `bash run_tests.sh` with no arguments is an equivalent Peano-only
shortcut and works from outside this directory as well.

The per-compiler targets are also available:

```sh
make xchesscc
make peano
make check
```

Use `make xchesscc` when XChessCC is explicitly requested. Use `make check`
when both compiler results are wanted; it continues through failures in both
backends.

If one compiler is not installed, its backend is marked `SKIP` and the other
backend still runs. If neither compiler is installed, the combined target
reports that no probes were run and exits with an error.

Each attempt is marked with colored `RUN`, `PASS`, or `FAIL` output, while an
unavailable backend is marked `SKIP`. Failed compiler output is retained in
`build/logs/<compiler>/`, and each target ends
with a total/pass/fail/skip summary. The overall command returns failure while
any available compiler probe fails; this is expected for `peano` until the
listed gaps are fixed. A skipped compiler does not count as a failure.
Set `VITIS_AIE_DIR`, `AIETOOLS_DIR`, `PEANO_INSTALL_DIR`, or `MLIR_AIE_DIR`
when the local tool installations are outside the repository's usual
environment.
