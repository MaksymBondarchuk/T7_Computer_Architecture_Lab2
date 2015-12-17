all:
		g++ -pg -std=c++11 -o main main.cpp Decoder/Decoder.h Decoder/Decoder.cpp
		valgrind --leak-check=yes ./main encode
