CXX         := gcc
CXX_FLAGS   := -s -Wall -std=c99

LIBRARIES   := -lraylib -lm -lpthread -ldl -lrt -lX11
EXECUTABLE  := app

all: run
	@rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

$(EXECUTABLE): ./src/*.c
	$(CXX) $(CXX_FLAGS) -I. $^ -o $@ $(LIBRARIES)
