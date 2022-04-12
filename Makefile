src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)
HEADERS_DIR = -I hdr

CC = g++

DEBUG = -g

COMPILER_FLAGS = -g -Wall -Wextra --pedantic -Wsign-conversion

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

game: $(obj)
	$(CC) $(LINKER_FLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(COMPILER_FLAGS) $(HEADERS_DIR) -o $@ -c $^

.PHONY: run
run:
	./game

.PHONY: clean
clean:
	rm game
	rm src/*.o
