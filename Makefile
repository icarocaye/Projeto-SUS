# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Diretórios
SRC_DIR = .
TADS_DIR = TADS

# Arquivos fonte
SRC = $(SRC_DIR)/main.c $(wildcard $(TADS_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Nome do executável
TARGET = prontosocorro

# Regra padrão
all: $(TARGET)

# Como gerar o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Como gerar arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean
