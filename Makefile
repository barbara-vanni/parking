# TARGET := parking
# CXX := g++

# SRCS_FOLDER := src
# INCLUDE_FOLDER := include
# PREREQUISITES_FOLDER := prerequisites
# OBJS_FOLDER := objs
# BIN_FOLDER := .

# SDL_INCLUDE := -I./include

# CXXFLAGS := -Wall -Wextra -flto -O1 -std=c++11 -I$(INCLUDE_FOLDER) -I$(PREREQUISITES_FOLDER) -I$(SDL_INCLUDE) -MMD
# LDFLAGS := -L./lib/

# SRCS_RAW := main.cpp \
# 			game/graphic_game/cpp_files/Window.cpp 


# SRCS := $(addprefix $(SRCS_FOLDER)/, $(SRCS_RAW))
# OBJS := $(SRCS:$(SRCS_FOLDER)/%.cpp=$(OBJS_FOLDER)/%.o)
# DEPS := $(OBJS:.o=.d)
# PREREQUISITES := $(wildcard $(PREREQUISITES_FOLDER)/*.cpp)

# .PHONY: all clean re fclean test

# all: $(TARGET)

# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_FOLDER)/$@ $^ -lSDL2 -lSDL2_ttf -lSDL2_image

# $(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.cpp | $(OBJS_FOLDER)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

# -include $(DEPS)

# $(OBJS_FOLDER):
# 	mkdir -p $(OBJS_FOLDER)

# clean:
# 	$(RM) $(OBJS) $(DEPS)

# fclean: clean
# 	$(RM) $(BIN_FOLDER)/$(TARGET)

# re: fclean all

# test: all
# 	$(BIN_FOLDER)/$(TARGET) grille




all:
	g++ -I src/include -L src/lib -o main main.cpp game/graphic_game/cpp_files/Window.cpp game/Grid.cpp -lmingw32 -lSDL2main -lSDL2