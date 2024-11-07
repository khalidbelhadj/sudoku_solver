SRC_DIR = src
BUILD_DIR = build
CC = clang
EMCC = emcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -Wall -Wextra -std=c11

all: $(OBJ_FILES)
	$(EMCC) $(OBJ_FILES) $(LIBRARY_PATHS) -o $(BUILD_DIR)/main

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(EMCC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@


clean:
	rm -r $(BUILD_DIR)/*

.PHONY: all clean