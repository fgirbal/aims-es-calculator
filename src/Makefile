EXE = string_calculator
SRC = $(wildcard *.cpp)
OBJ = $(addprefix build/,$(SRC:.cpp=.o))

all: $(EXE)

$(EXE): $(OBJ)
	@echo 'Building target: $(EXE)'
	@echo 'Invoking: C Linker'
	g++ -lpthread -o $(EXE) $(OBJ)
	@echo 'Finished building target: $(EXE)'
	@echo ' '

build/%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: G++ C Compiler'
	g++ -std=c++11 -O0 -g -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

clean:
	rm -f build/*.o $(EXE)*
