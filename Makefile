# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Iinclude

# Libraries
LDFLAGS = -lyaml

# Source files
SRC = src/main.c src/parser.c

# Object files
OBJ = $(SRC:.c=.o)

# Output Executable
TARGET = zepto

# Build Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean