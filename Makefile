# Source directory
SRC_DIR = source
# Object directory
OBJ_DIR = build
# include directory
IDIR = include

# compiler info
CC = g++
CFLAGS = -I$(IDIR)

# List of source files (excluding main.cpp)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# List of object files corresponding to source files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable name
EXECUTABLE = my_program

# Libraries needed for cURL
LIBS = -lcurl

# Rule to build the executable
$(EXECUTABLE): $(OBJ_DIR)/main.o $(OBJS)
	$(CC) -o $(OBJ_DIR)/$@ $^ $(CFLAGS) $(LIBS)

# Rule to compile main.cpp into an object file
$(OBJ_DIR)/main.o: main.cpp $(IDIR)/json.h | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to compile other source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(IDIR)/json.h | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

# Ensure that the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

run:
	./$(OBJ_DIR)/$(EXECUTABLE)