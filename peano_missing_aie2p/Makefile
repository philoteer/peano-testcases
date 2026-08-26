##===- Makefile -----------------------------------------------------------===##
# Compile-only regression probes for Peano on XDNA2 / aie2p.

.DEFAULT_GOAL := aie2p

srcdir := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

SOURCES := \
	portable_vector.cc \
	bfloat16_vector_accum.cc \
	cint16_vector_accum.cc \
	cint16_components_magsq.cc \
	complex_vector_components.cc \
	phase_u32_acc64.cc \
	unaligned_complex_io.cc \
	complex_scalar_ops.cc \
	complex_vector_scalar_add.cc \
	scoped_mode.cc \
	constexpr_complex_table.cc \
	sliding_cacc64.cc \
	cacc64_cast.cc \
	threshold_pipeline.cc \
	threshold_accum_mac_msc.cc \
	fft_r4_stage.cc \
	libm_float_functions.cc

BUILD_DIR ?= build

PEANO_INSTALL_DIR ?= $(shell python3 -c "import sysconfig; print(sysconfig.get_paths()['purelib'] + '/llvm-aie')" 2>/dev/null)
MLIR_AIE_DIR ?= $(shell python3 -c "from aie.utils.config import root_path; print(root_path())" 2>/dev/null)

.PHONY: aie2p peano clean

aie2p: peano

peano:
	@BUILD_DIR="$(BUILD_DIR)" PEANO_INSTALL_DIR="$(PEANO_INSTALL_DIR)" \
		MLIR_AIE_DIR="$(MLIR_AIE_DIR)" bash "$(srcdir)/run_tests.sh" peano $(SOURCES)

clean:
	rm -rf "$(BUILD_DIR)"
