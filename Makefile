# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinc

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build/obj
BIN_DIR = build/bin

# Source files grouped into categories
SRC_FILES = $(wildcard $(SRC_DIR)/command/*.cpp) \
            $(wildcard $(SRC_DIR)/core/*.cpp) \
            $(wildcard $(SRC_DIR)/utils/*.cpp) \
            $(SRC_DIR)/krypton.cpp  # Entry point

# Convert source files into object file paths
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Output executable name
TARGET = $(BIN_DIR)/krypton.exe  # .exe required on Windows

# PDCurses Library
LIBS = -lpdcurses

# Ensure necessary directories exist (Windows version)
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)" & if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
    RM = rmdir /s /q
    DEL = del /s /q
else
    MKDIR = mkdir -p $(OBJ_DIR) $(BIN_DIR)
    RM = rm -rf
    DEL = rm -f
endif

# Build executable
$(TARGET): $(OBJ_FILES)
	$(MKDIR)
	$(CXX) -o $(TARGET) $(OBJ_FILES) $(LIBS) $(CXXFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files (Windows & Linux compatible)
clean:
	-$(DEL) $(OBJ_DIR)\*.o
	-$(DEL) $(BIN_DIR)\krypton.exe