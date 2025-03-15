# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinc

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build/obj
BIN_DIR = build/bin
RES_DIR = assets/resources
ICON_FILE = assets/icons/krypton.ico
RC_FILE = $(RES_DIR)/icon.rc
RES_FILE = $(RES_DIR)/krypton.res  # Store the compiled resource in assets/resources/

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
$(TARGET): $(OBJ_FILES) $(RES_FILE)
	$(MKDIR)
	$(CXX) -o $(TARGET) $(OBJ_FILES) $(RES_FILE) $(LIBS) $(CXXFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile resource file into .res (stored in assets/resources/)
$(RES_FILE): $(RC_FILE) $(ICON_FILE)
	windres $(RC_FILE) -O coff -o $(RES_FILE)

# Clean build files (Windows & Linux compatible)
clean:
	-for /r "$(OBJ_DIR)" %%f in (*.o) do del "%%f"
	-if exist "$(BIN_DIR)\krypton.exe" del /q "$(BIN_DIR)\krypton.exe"
	-for /r "$(RES_DIR)" %%f in (*.res) do del "%%f"