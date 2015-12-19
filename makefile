all:
		g++ -std=c++14 -pthread -o main main.cpp Decoder/Decoder.hpp
		valgrind --leak-check=yes ./main
		rm -f main
