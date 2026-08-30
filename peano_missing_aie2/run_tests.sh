#!/usr/bin/env bash

set -u

if (( $# == 0 )); then
  exec make -C "$(dirname -- "${BASH_SOURCE[0]}")"
fi

compiler="$1"
shift
build_dir="${BUILD_DIR:-build}"
source_count=$#

skip_compiler() {
  local reason="$1"
  printf '\033[33m[SKIP]\033[0m %s: %s; skipped %d probes\n' \
    "$compiler" "$reason" "$source_count"
  printf '\033[1;36mSummary (%s)\033[0m total=%d pass=\033[32m0\033[0m fail=\033[31m0\033[0m skip=\033[33m%d\033[0m\n' \
    "$compiler" "$source_count" "$source_count"
  exit 0
}

case "$compiler" in
  xchesscc)
    command -v xchesscc_wrapper >/dev/null 2>&1 ||
      skip_compiler "xchesscc_wrapper is not installed"
    command -v xchesscc >/dev/null 2>&1 ||
      skip_compiler "xchesscc is not installed"
    command -v chesscc >/dev/null 2>&1 ||
      skip_compiler "chesscc is not installed or not on PATH"
    [[ -n "${AIETOOLS_DIR:-}" ]] ||
      skip_compiler "AIETOOLS_DIR is not configured"
    compiler_command=(
      xchesscc_wrapper
      aie2
      "-I${AIETOOLS_DIR}/include"
    )
    ;;
  peano)
    [[ -x "${PEANO_INSTALL_DIR:-}/bin/clang++" ]] ||
      skip_compiler "Peano clang++ is not installed"
    [[ -n "${MLIR_AIE_DIR:-}" ]] ||
      skip_compiler "MLIR_AIE_DIR is not configured"
    compiler_command=(
      "${PEANO_INSTALL_DIR}/bin/clang++"
      -O2
      -std=c++20
      --target=aie2-none-unknown-elf
      -Wno-parentheses
      -Wno-attributes
      -Wno-macro-redefined
      -Wno-empty-body
      -Wno-missing-template-arg-list-after-template-kw
      -DNDEBUG
      "-I${MLIR_AIE_DIR}/include"
      -D__AIE_API_AIE_ADF_HPP__
    )
    ;;
  *)
    printf 'Unknown compiler: %s\n' "$compiler" >&2
    exit 2
    ;;
esac

mkdir -p "${build_dir}/${compiler}" "${build_dir}/logs/${compiler}"

total=0
passed=0
failed=0

for source in "$@"; do
  base="${source%.cc}"
  output="${build_dir}/${compiler}/${base}.o"
  log="${build_dir}/logs/${compiler}/${base}.log"
  total=$((total + 1))

  printf '\033[36m[RUN]\033[0m %s/%s\n' "$compiler" "$source"
  if "${compiler_command[@]}" -c "$source" -o "$output" >"$log" 2>&1; then
    passed=$((passed + 1))
    printf '\033[32m[PASS]\033[0m %s/%s\n' "$compiler" "$source"
  else
    failed=$((failed + 1))
    printf '\033[31m[FAIL]\033[0m %s/%s\n' "$compiler" "$source"
    printf '       log: %s\n' "$log"
  fi
done

printf '\033[1;36mSummary (%s)\033[0m total=%d pass=\033[32m%d\033[0m fail=\033[31m%d\033[0m skip=\033[33m0\033[0m\n' \
  "$compiler" "$total" "$passed" "$failed"

if ((failed != 0)); then
  exit 1
fi
