all:
		g++ -std=c++14 -o main main.cpp Decoder/Decoder.h Decoder/Decoder.cpp
		valgrind --leak-check=yes ./main
		rm -f main
