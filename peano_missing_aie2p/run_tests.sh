#!/usr/bin/env bash

set -u

srcdir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)

if (( $# == 0 )); then
  exec make -C "$srcdir"
fi

compiler="$1"
shift
source_count=$#
build_dir="${BUILD_DIR:-build}"

if [[ "$compiler" != peano ]]; then
  printf 'Unknown compiler: %s\n' "$compiler" >&2
  exit 2
fi

skip_compiler() {
  local reason="$1"
  printf '\033[33m[SKIP]\033[0m peano: %s; skipped %d probes\n' \
    "$reason" "$source_count"
  printf '\033[1;36mSummary (peano)\033[0m total=%d pass=\033[32m0\033[0m fail=\033[31m0\033[0m skip=\033[33m%d\033[0m\n' \
    "$source_count" "$source_count"
  exit 2
}

[[ -x "${PEANO_INSTALL_DIR:-}/bin/clang++" ]] ||
  skip_compiler "Peano clang++ is not installed"
[[ -n "${MLIR_AIE_DIR:-}" ]] ||
  skip_compiler "MLIR_AIE_DIR is not configured"

compiler_command=(
  "${PEANO_INSTALL_DIR}/bin/clang++"
  -O2
  -std=c++20
  --target=aie2p-none-unknown-elf
  -Wno-parentheses
  -Wno-attributes
  -Wno-macro-redefined
  -Wno-empty-body
  -Wno-missing-template-arg-list-after-template-kw
  -DNDEBUG
  "-I${MLIR_AIE_DIR}/include"
)

cd "$srcdir"
mkdir -p "${build_dir}/peano" "${build_dir}/logs/peano"

total=0
passed=0
failed=0

for source in "$@"; do
  base="${source%.cc}"
  output="${build_dir}/peano/${base}.o"
  log="${build_dir}/logs/peano/${base}.log"
  total=$((total + 1))

  printf '\033[36m[RUN]\033[0m peano/%s\n' "$source"
  if "${compiler_command[@]}" -c "$source" -o "$output" >"$log" 2>&1; then
    passed=$((passed + 1))
    printf '\033[32m[PASS]\033[0m peano/%s\n' "$source"
  else
    failed=$((failed + 1))
    printf '\033[31m[FAIL]\033[0m peano/%s\n' "$source"
    printf '       log: %s\n' "$log"
  fi
done

printf '\033[1;36mSummary (peano)\033[0m total=%d pass=\033[32m%d\033[0m fail=\033[31m%d\033[0m skip=\033[33m0\033[0m\n' \
  "$total" "$passed" "$failed"

if ((failed != 0)); then
  exit 1
fi
