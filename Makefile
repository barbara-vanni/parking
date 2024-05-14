
all:
	g++ -I src/include -L src/lib -o main main.cpp game/graphic_game/cpp_files/Window.cpp -lmingw32 -lSDL2main -lSDL2