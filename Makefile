src = $(wildcard src/*.cpp)
obj = $(src:.c=.o)
HEADERS_DIR = -I hdr

CC = g++

DEBUG = -g

COMPILER_FLAGS = -Wall -Wextra --pedantic -Wsign-conversion

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

game: $(obj)
	$(CC) $(DEBUG) $(HEADERS_DIR) -o $@ $^ $(LINKER_FLAGS) $(COMPILER_FLAGS)

.PHONY: run
run:
	./game

.PHONY: clean
clean:
	rm game
