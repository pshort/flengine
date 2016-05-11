CC=clang++
C-FLAGS=-g -fPIC -c -Wall -std=c++11
C-FLAGS-LINK=-shared -g -Wall -std=c++11 -lSDL2 -lSDL2_image -lSDL2_ttf
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:src/%.cpp=build/%.o)
BUILD_PATH=$(wildcard ./build)
LIB_PATH=$(wildcard ./build/lib)
INC_PATH=$(wildcard ./build/include)

all: clean prep $(OBJ) lib remove_o

prep:
	mkdir build
	mkdir build/lib
	mkdir build/include
	cp src/*.h build/include

remove_o:
	rm build/*.o

lib: $(OBJ)
	$(CC) -o $(LIB_PATH)/flengine.so $(OBJ) $(C-FLAGS-LINK)

# $@ refers to the targt (which in this case is build all .cpp files into .o its special)
# $< refers to the arguments (which are automatically the cpp files)
build/%.o: src/%.cpp
	$(CC) $(C-FLAGS) $< -o $@

clean:
	rm build -rf
