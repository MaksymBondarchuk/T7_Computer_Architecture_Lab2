all:
		g++ -pg -std=c++14 -o main main.cpp Decoder/Decoder.h Decoder/Decoder.cpp
		valgrind --leak-check=yes ./main encode
