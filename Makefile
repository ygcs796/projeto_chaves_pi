# Nome do executável
PROJECT_NAME = chaves

# Caminho da Raylib dentro do repositório
RAYLIB_DIR = deps/raylib
INCLUDE_DIR = $(RAYLIB_DIR)/include
LIB_DIR = $(RAYLIB_DIR)/lib

# Compilador
CC = gcc

# Flags
CFLAGS = -std=c99 -Wall -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm

# Arquivos .c automaticamente
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Regra principal
all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJ)
	$(CC) $(OBJ) -o $(PROJECT_NAME) $(LDFLAGS)

# Compilar cada .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar
clean:
	del /Q *.o *.exe

