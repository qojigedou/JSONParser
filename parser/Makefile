CC = g++
CFLAGS = -std=c++11

NAME = parserJSON
OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin
INC_DIR = $(SRC_DIR)/include

OUT = main
BINARIES = $(addprefix $(BIN_DIR)/, $(OUT))
DEPS = inputDriver lexer token array object parser 
DEPS_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(DEPS)))
DEPS_INC = $(addprefix $(INC_DIR)/, $(addsuffix .h, $(DEPS)))
TEMPLATES =
TEMPLATES_INC = $(addprefix $(INC_DIR)/, $(addsuffix .h, $(TEMPLATES)))

.PRECIOUS: $(OBJ_DIR)/%.o
.PHONY: clean structure all run

all: $(BINARIES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(DEPS_OBJ) | structure
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h $(TEMPLATES_INC) | structure
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(TEMPLATES_INC) | structure
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN_DIR)/$(OUT)

structure:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

zip: clean
	zip -r ../$(NAME).zip ../$(NAME)
tar: clean
	tar cvfz ../$(NAME).tar.gz ../$(NAME)
