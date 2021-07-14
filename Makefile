PROJECT = simple-cli

BUILD_DIR = build

SRC = \
	src/platform/x64/main.c \
	src/cli/cli.c \

INC = \
	-Isrc/platform/x64 \
	-Isrc/cli \

BIN_FILE = $(BUILD_DIR)/$(PROJECT)

all: $(SRC)
	mkdir -p $(BUILD_DIR)
	gcc $(INC) $(SRC) -o $(BIN_FILE)

clean:
	rm -rf $(BUILD_DIR)