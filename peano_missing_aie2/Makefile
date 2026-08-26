##===- Makefile -----------------------------------------------------------===##
# Compile-only regression probes for compiler features used by the kernels.

.DEFAULT_GOAL := all

srcdir := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

SOURCES := \
	portable_vector.cc \
	complex_scalar_ops.cc \
	complex_vector_scalar_add.cc \
	complex_vector_scalar_add_cbfloat16.cc \
	constexpr_complex_table.cc \
	cacc64_cast.cc \
	libm_float_functions.cc \
	scoped_mode.cc \
	sliding_cacc64.cc

BUILD_DIR ?= build

# The default layout is the one used by vitis_aie_essentials. Override this
# variable for another Vitis AIE installation.
XCHESSCC_PATH := $(shell PATH="$(PATH)" command -v xchesscc 2>/dev/null)
VITIS_AIE_DIR ?= $(if $(XCHESSCC_PATH),$(shell realpath $(dir $(XCHESSCC_PATH))/../../..),)
AIETOOLS_DIR ?= $(VITIS_AIE_DIR)

PEANO_INSTALL_DIR ?= $(shell python3 -c "import sysconfig; print(sysconfig.get_paths()['purelib'] + '/llvm-aie')" 2>/dev/null)
MLIR_AIE_DIR ?= $(shell python3 -c "from aie.utils.config import root_path; print(root_path())" 2>/dev/null)

XCHESSCC_AVAILABLE := $(shell test -n "$(XCHESSCC_PATH)" && PATH="$(PATH)" command -v xchesscc_wrapper >/dev/null 2>&1 && printf yes || printf no)
PEANO_AVAILABLE := $(shell test -x "$(PEANO_INSTALL_DIR)/bin/clang++" && printf yes || printf no)

XCHESSCC_ENV :=
ifneq ($(VITIS_AIE_DIR),)
XCHESSCC_ENV := PATH=$(VITIS_AIE_DIR)/tps/lnx64/target_aie_ml/bin/LNa64bin:$(PATH) \
	LD_LIBRARY_PATH=$(VITIS_AIE_DIR)/lib/lnx64.o:$(LD_LIBRARY_PATH)
endif

.PHONY: all check xchesscc peano clean

all:
	@if [ "$(XCHESSCC_AVAILABLE)" = no ] && [ "$(PEANO_AVAILABLE)" = no ]; then \
		printf '\033[33m[SKIP]\033[0m no xchesscc or Peano compiler is available; no probes were run\n'; \
		exit 2; \
	fi
	+$(MAKE) --no-print-directory peano

check:
	@if [ "$(XCHESSCC_AVAILABLE)" = no ] && [ "$(PEANO_AVAILABLE)" = no ]; then \
		printf '\033[33m[SKIP]\033[0m no xchesscc or Peano compiler is available; no probes were run\n'; \
		exit 2; \
	fi
	+$(MAKE) --no-print-directory -k xchesscc peano

xchesscc:
	@$(XCHESSCC_ENV) BUILD_DIR="$(BUILD_DIR)" AIETOOLS_DIR="$(AIETOOLS_DIR)" \
		bash "$(srcdir)/run_tests.sh" xchesscc $(SOURCES)

peano:
	@BUILD_DIR="$(BUILD_DIR)" PEANO_INSTALL_DIR="$(PEANO_INSTALL_DIR)" \
		MLIR_AIE_DIR="$(MLIR_AIE_DIR)" bash "$(srcdir)/run_tests.sh" peano $(SOURCES)

clean:
	rm -rf $(BUILD_DIR)
