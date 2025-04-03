CC = gcc
INCLUDE = -Iinclude -IThirdparty 
CFLAGS = $(INCLUDE) -Wall -g      
LIBS = lib/libfdr.a        

EXECUTABLES = bin/program

SRC_DIR = src
OBJ_DIR = obj

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(EXECUTABLES)

bin/program: $(OBJECTS)
	@mkdir -p bin  
	$(CC) $(OBJECTS) -o bin/program $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLES)

.PHONY: all clean