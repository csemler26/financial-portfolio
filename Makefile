# Source directory
SRC_DIR = src
# Object directory
OBJ_DIR = build
# include directory
IDIR = include

# UltimateDSA dependency
ULTIMATE_DSA_DIR = UltimateDSA
ULTIMATE_DSA_SRC_DIR = $(ULTIMATE_DSA_DIR)/src
ULTIMATE_DSA_SRCS = $(wildcard $(ULTIMATE_DSA_SRC_DIR)/*.cpp)
ULTIMATE_DSA_INC_DIR = $(ULTIMATE_DSA_DIR)/include

# compiler info
CC = g++
CFLAGS = -I$(IDIR) -I$(ULTIMATE_DSA_INC_DIR) -std=c++20

# List of source files (excluding main.cpp and UltimateDSA sources)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# List of object files corresponding to source files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS)) $(patsubst $(ULTIMATE_DSA_SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(ULTIMATE_DSA_SRCS))

# Executable name
EXECUTABLE = my_program

# External Libraries
LIBS = -lcurl -lsqlite3

# Rule to build the executable
$(OBJ_DIR)/$(EXECUTABLE): $(OBJS) $(OBJ_DIR)/main.o | $(OBJ_DIR)
	@echo "generating: $@"
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Rule to compile main.cpp into an object file
$(OBJ_DIR)/main.o: main.cpp $(wildcard $(IDIR)/*.h) $(wildcard $(ULTIMATE_DSA_INC_DIR)/*.h) | $(OBJ_DIR)
	@echo "generating: $@"
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to compile other source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(IDIR)/%.h | $(OBJ_DIR)
	@echo "generating: $@"
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to compile UltimateDSA source files into object files
$(OBJ_DIR)/%.o: $(ULTIMATE_DSA_SRC_DIR)/%.cpp $(ULTIMATE_DSA_INC_DIR)/%.h | $(OBJ_DIR)
	@echo "generating: $@"
	$(CC) -c -o $@ $< $(CFLAGS)

# Ensure that the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)

run:
	./$(OBJ_DIR)/$(EXECUTABLE)