src = $(wildcard src/*.cpp)
obj = $(src:.c=.o)
HEADERS_DIR = -I hdr

CC = g++

COMPILER_FLAGS = -Wall -Wextra --pedantic -Wsign-conversion

LINKER_FLAGS = -lSDL2 -lSDL2_image

game: $(obj)
	$(CC) $(HEADERS_DIR) -o $@ $^ $(LINKER_FLAGS) $(COMPILER_FLAGS)

.PHONY: clean
clean:
	rm game
