all:
	 g++ -std=c++17 \
	     -Isrc/include \
	     main.cpp \
	     -Lsrc/lib \
	     -lmingw32 -lSDL2main -lSDL2 \
	     -mwindows \
	     -o main.exe
