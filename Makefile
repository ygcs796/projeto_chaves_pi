# Nome do executável
PROJECT_NAME = chaves

# Caminho da Raylib dentro do repositório
RAYLIB_DIR = deps/raylib
INCLUDE_DIR = $(RAYLIB_DIR)/include
LIB_DIR = $(RAYLIB_DIR)/lib

# Diretório dos headers do jogo
FASE1_INCLUDE = fase1
FASE2_INCLUDE = fase2

# Compilador
CC = gcc

# Flags
CFLAGS = -std=c99 -Wall -I$(INCLUDE_DIR) -I$(FASE1_INCLUDE) -I$(FASE2_INCLUDE)
LDFLAGS = -L$(LIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm

# Arquivos .c automaticamente
SRC = $(wildcard *.c) $(wildcard fase1/*.c)
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
