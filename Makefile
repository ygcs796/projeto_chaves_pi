# ===========================
# Configurações gerais
# ===========================
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Isrc -Iinclude
BIN = game

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))


# ===========================
# Detectar sistema
# ===========================
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    PLATFORM = MACOS
else
    PLATFORM = WINDOWS
endif



# ===========================
# Config macOS
# ===========================
ifeq ($(PLATFORM), MACOS)

RAYLIB_LIB = deps/raylib/mac/lib
RAYLIB_INC = deps/raylib/mac/include

CFLAGS += -I$(RAYLIB_INC)

LDFLAGS = -L$(RAYLIB_LIB) \
          -lraylib \
          -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL \
          -Wl,-rpath,@executable_path/$(RAYLIB_LIB)

endif


# ===========================
# Config Windows
# ===========================
ifeq ($(PLATFORM), WINDOWS)

RAYLIB_LIB = deps/raylib/windows/lib
RAYLIB_INC = deps/raylib/windows/include

CFLAGS += -I$(RAYLIB_INC)

LDFLAGS = -L$(RAYLIB_LIB) -lraylib -lopengl32 -lgdi32 -lwinmm

endif



# ===========================
# Regras principais
# ===========================
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@



# ===========================
# Limpeza
# ===========================
clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
