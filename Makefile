all:
	g++ -I src/include -L src/lib -o main RGA.cpp Init_Game.cpp Map.cpp Wall.cpp Ball.cpp Physics.cpp Render.cpp -lmingw32 -lSDL2main -lSDL2 