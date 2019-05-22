PROJ_NAME=goldminer

# .cpp files
CXX_SRC=$(wildcard ./src/*.cpp)
CXX_SRC_APP=$(wildcard ./app/*.cpp)

# .h files
H_SRC=$(wildcard ./include/*.h)
H_SRC_APP=$(wildcard ./app/*.h)

# Object files
OBJ=$(subst .cpp,.o,$(subst src,objects,$(CXX_SRC)))
OBJ_APP=$(subst .cpp,.o,$(subst app,objects,$(CXX_SRC_APP)))

# Compiler and linker
CXX=g++

# Flags for compiler
CXX_FLAGS=-c        \
          -W        \
          -Wall     \
          -ansi     \
          -pedantic \
          -g        \
          -std=c++17

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: create_folders $(PROJ_NAME)

# $^ expands to all target prerequisites
$(PROJ_NAME): $(OBJ_APP) $(OBJ)
	@ echo "Building target using G++ compiler: $<"
	@ $(CXX) $^ -o ./app/release/$@
	@ echo "Finished building binary: $@"
	@ echo " "

run:
	@ ./app/release/$(PROJ_NAME)

# $@ get the target's name
# $< get the first prerequisite's name
./objects/%.o: ./src/%.cpp ./include/%.h
	@ echo "Bulding target using G++ compiler: $<"
	@ $(CXX) $< $(CXX_FLAGS) -o $@
	@ echo " "

./objects/main.o: ./app/main.cpp $(H_SRC_APP)
	@ echo "Bulding target using G++ compiler: $<"
	@ $(CXX) $< $(CXX_FLAGS) -o $@
	@ echo " "

clean:
	@ $(RM) ./objects/*.o ./bin/* $(PROJ_NAME) *~
	@ rmdir --ignore-fail-on-non-empty objects
	@ rmdir --ignore-fail-on-non-empty bin

create_folders:
	@ mkdir -p bin
	@ mkdir -p objects

########## MINE GENERATOR ##########

%:
	@:

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

generate:
	@ g++ -o generator/generate generator/generator.cpp generator/mine_generator.cpp
	@ ./generator/generate $(call args,defaultstring)

.PHONY: all clean