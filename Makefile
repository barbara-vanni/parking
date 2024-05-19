# all:
# 	g++ -I src/include -L src/lib -o main main.cpp game/graphic_game/cpp_files/Window.cpp game/logic_game/cpp_files/Car.cpp game/logic_game/cpp_files/StockCar.cpp game/logic_game/cpp_files/GameObject.cpp game/graphic_game/cpp_files/graphicInit.cpp game/Grid.cpp game/gameLoop.cpp game/graphic_game/cpp_files/Button.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf 

# Compiler and linker
CXX := g++
CXXFLAGS := -I src/include
LDFLAGS := -L src/lib
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Directories
SRC_DIR := game
GRAPHIC_DIR := $(SRC_DIR)/graphic_game/cpp_files
LOGIC_DIR := $(SRC_DIR)/logic_game/cpp_files

# Source files
SRC_FILES := main.cpp \
             $(GRAPHIC_DIR)/Window.cpp \
             $(LOGIC_DIR)/Car.cpp \
             $(LOGIC_DIR)/StockCar.cpp \
             $(LOGIC_DIR)/GameObject.cpp \
             $(GRAPHIC_DIR)/graphicInit.cpp \
             $(SRC_DIR)/Grid.cpp \
             $(SRC_DIR)/gameLoop.cpp \
             $(GRAPHIC_DIR)/Button.cpp

# Object files
OBJ_FILES := $(SRC_FILES:.cpp=.o)

# Executable
TARGET := main

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Phony targets
.PHONY: all clean
