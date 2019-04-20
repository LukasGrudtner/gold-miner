PROJ_NAME=goldminer

# .cpp files
CXX_SRC=$(wildcard ./src/*.cpp)

# .h files
H_SRC=$(wildcard ./include/*.h)

# Object files
OBJ=$(subst .cpp,.o,$(subst src,objects,$(CXX_SRC)))

# Compiler and linker
CXX=g++

# Flags for compiler
CXX_FLAGS=-c        \
          -W        \
          -Wall     \
          -ansi     \
          -pedantic \
          -g

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: objFolder binFolder $(PROJ_NAME)

# $^ expands to all target prerequisites
$(PROJ_NAME): $(OBJ)
	@ echo "Building target using G++ compiler: $<"
	$(CXX) $^ -o ./bin/$@
	@ echo "Finished building binary: $@"
	@ echo " "

# $@ get the target's name
# $< get the first prerequisite's name
./objects/%.o: ./src/%.cpp ./include/%.h
	@ echo "Bulding target using G++ compiler: $<"
	$(CXX) $< $(CXX_FLAGS) -o $@
	@ echo " "

./objects/main.o: ./src/main.cpp $(H_SRC)
	@ echo "Bulding target using G++ compiler: $<"
	$(CXX) $< $(CXX_FLAGS) -o $@
	@ echo " "

objFolder:
	@ mkdir -p objects

binFolder:
	@ mkdir -p bin

clean:
	@ $(RM) ./objects/*.o ./bin/* $(PROJ_NAME) *~
	@ rmdir objects
	@ rmdir bin

.PHONY: all clean