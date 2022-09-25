CXX         := gcc
CXX_FLAGS   := 

LIBRARIES   := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
EXECUTABLE  := app

all: run
	@rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

$(EXECUTABLE): ./src/*.c
	$(CXX) $(CXX_FLAGS) -I. $^ -o $@ $(LIBRARIES)
