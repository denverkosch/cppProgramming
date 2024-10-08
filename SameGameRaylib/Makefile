# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug_x64
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_x64)
  raylib_config = debug_x64
  SameGameRaylib_config = debug_x64

else ifeq ($(config),debug_x86)
  raylib_config = debug_x86
  SameGameRaylib_config = debug_x86

else ifeq ($(config),debug_arm64)
  raylib_config = debug_arm64
  SameGameRaylib_config = debug_arm64

else ifeq ($(config),release_x64)
  raylib_config = release_x64
  SameGameRaylib_config = release_x64

else ifeq ($(config),release_x86)
  raylib_config = release_x86
  SameGameRaylib_config = release_x86

else ifeq ($(config),release_arm64)
  raylib_config = release_arm64
  SameGameRaylib_config = release_arm64

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := raylib SameGameRaylib

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

raylib:
ifneq (,$(raylib_config))
	@echo "==== Building raylib ($(raylib_config)) ===="
	@${MAKE} --no-print-directory -C _build -f raylib.make config=$(raylib_config)
endif

SameGameRaylib: raylib
ifneq (,$(SameGameRaylib_config))
	@echo "==== Building SameGameRaylib ($(SameGameRaylib_config)) ===="
	@${MAKE} --no-print-directory -C _build -f SameGameRaylib.make config=$(SameGameRaylib_config)
endif

clean:
	@${MAKE} --no-print-directory -C _build -f raylib.make clean
	@${MAKE} --no-print-directory -C _build -f SameGameRaylib.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_x64"
	@echo "  debug_x86"
	@echo "  debug_arm64"
	@echo "  release_x64"
	@echo "  release_x86"
	@echo "  release_arm64"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   raylib"
	@echo "   SameGameRaylib"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"