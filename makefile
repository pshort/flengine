CC=clang++
C-FLAGS=-g -c -Wall -std=c++11
C-FLAGS-LINK=-g -Wall -std=c++11 -lSDL2 -lSDL2_image -lSDL2_ttf
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:src/%.cpp=build/%.o)
BUILD_PATH=$(wildcard ./build)
LIB_PATH=$(wildcard ./build/lib)
INC_PATH=$(wildcard ./build/include)

all: $(OBJ)

prep:
	mkdir build
	mkdir build/lib
	mkdir build/include
	cp src/*.h build/include

lib: $(OBJ)
	$(CC) -shared -undefined dynamic_lookup -o build/lib/flengine.0.0.1.so $<

# $@ refers to the targt (which in this case is build all .cpp files into .o its special)
# $< refers to the arguments (which are automatically the cpp files)
build/%.o: src/%.cpp
	$(CC) $(C-FLAGS) $< -o $@

clean:
	rm build -rf
