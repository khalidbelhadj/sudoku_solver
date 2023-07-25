SRC_DIR = src
BUILD_DIR = build/debug
CC = clang
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_NAME = run
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -Wall -Wextra -g
# LINKER_FLAGS = -lsdl2


WASM_COMPILER_FLAGS = --target=wasm32 -nostdlib -O3 -Wl,--no-entry -Wl,--export-all -Wl,--lto-O3 -Wl,--allow-undefined

wasm:
	$(CC) $(WASM_COMPILER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME).wasm

output:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

NAME:
	rm -r $(BUILD_DIR)/*
