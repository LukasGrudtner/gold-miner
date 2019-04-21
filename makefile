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
          -g        \
          -std=c++11

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: create_folders $(PROJ_NAME)

# $^ expands to all target prerequisites
$(PROJ_NAME): $(OBJ)
	@ echo "Building target using G++ compiler: $<"
	@ $(CXX) $^ -o ./bin/$@
	@ echo "Finished building binary: $@"
	@ echo " "

# $@ get the target's name
# $< get the first prerequisite's name
./objects/%.o: ./src/%.cpp ./include/%.h
	@ echo "Bulding target using G++ compiler: $<"
	@ $(CXX) $< $(CXX_FLAGS) -o $@
	@ echo " "

./objects/main.o: ./src/main.cpp $(H_SRC)
	@ echo "Bulding target using G++ compiler: $<"
	@ $(CXX) $< $(CXX_FLAGS) -o $@
	@ echo " "

clean:
	@ $(RM) ./objects/*.o ./bin/* ./test/objects/*.o ./test/bin/* $(PROJ_NAME) *~
	@ rmdir --ignore-fail-on-non-empty objects
	@ rmdir --ignore-fail-on-non-empty bin
	@ rmdir --ignore-fail-on-non-empty test/objects
	@ rmdir --ignore-fail-on-non-empty test/bin

########## TESTS ##########

# .cpp test files
CXX_TEST_SRC=$(wildcard ./test/src/*.cpp)

# Test object files
OBJ_TEST=$(subst .cpp,.o,$(subst test/src,test/objects,$(CXX_TEST_SRC)))

# .hpp test files
HPP_TEST_SRC=$(wildcard ./test/include/*.hpp)

# Test object files
./test/objects/%.o: ./test/src/%.cpp $(H_SRC) $(HPP_TEST_SRC)
	@ $(CXX) $< $(CXX_FLAGS) -o $@

# Run all tests
test: create_folders run_tests

run_tests: $(OBJ) $(OBJ_TEST) 
	@ $(CXX) $^ -o ./test/bin/test
	@./test/bin/test

test-debug: $(OBJ) $(OBJ_TEST) 
	@ $(CXX) $^ -o ./test/bin/test
	@gdb test/bin/test
	

create_folders:
	@ mkdir -p bin
	@ mkdir -p objects
	@ mkdir -p test/bin
	@ mkdir -p test/objects

.PHONY: all clean test