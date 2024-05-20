CXX := g++
CXXFLAGS := -I src/include -I /usr/include/SDL2
LDFLAGS := -L src/lib
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

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

# Test target for image_test
imageTest: imageTest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

imageTest.o: imageTest.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ_FILES) $(TARGET) imageTest.o imageTest

# Phony targets
.PHONY: all clean imageTest
