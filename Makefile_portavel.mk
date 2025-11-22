# Nome do executável
PROJECT_NAME = chaves

# Caminho da Raylib dentro do repositório
RAYLIB_DIR = deps/raylib
INCLUDE_DIR = $(RAYLIB_DIR)/include
LIB_DIR = $(RAYLIB_DIR)/lib

# Compilador
CC = gcc

# Base flags
CFLAGS = -std=c99 -Wall -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) -lraylib

# Detectar sistema operacional
ifeq ($(OS),Windows_NT)
    # ---- WINDOWS ----
    PLATFORM = WINDOWS
    LDFLAGS += -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        # ---- LINUX ----
        PLATFORM = LINUX
        LDFLAGS += -lGL -lm -lpthread -ldl
        RM = rm -f
    endif

    ifeq ($(UNAME_S),Darwin)
        # ---- MACOS ----
        PLATFORM = MACOS
        LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
        RM = rm -f
    endif
endif

# Arquivos .c automaticamente
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Regra principal
all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJ)
	@echo Building for $(PLATFORM)
	$(CC) $(OBJ) -o $(PROJECT_NAME) $(LDFLAGS)

# Compilar cada .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar
clean:
	$(RM) *.o $(PROJECT_NAME)
