CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -O2
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
INCLUDE_PATHS = -I./src -I./include -I./external/raygui

ifeq ($(OS),Windows_NT)
    LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
else
    LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

all: mygame

mygame: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

clean:
	rm -f src/*.o mygame
