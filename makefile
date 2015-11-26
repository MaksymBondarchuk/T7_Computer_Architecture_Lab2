all:
		g++ -pg -std=c++11 -o main main.cpp Decoder/Decoder.h Decoder/Decoder.cpp

gprof:
		gprof main gmon.out > report.txt


profilerEncode0:
		g++ -pg -std=c++11 -o main main.cpp Decoder/Decoder.h Decoder/Decoder.cpp -O0 -pg
		./main encode
		gprof main gmon.out > report.txt
		gcc -c -std=c++11 -g -Wa,-a,-ad main.cpp > testE0.txt

profilerEncode3:
		g++ -pg -std=c++11 -o main main.cpp Decoder/Decoder.h Decoder/Decoder.cpp -O3 -pg
		./main encode
		gprof main gmon.out > report.txt
		gcc -c -std=c++11 -g -Wa,-a,-ad main.cpp > testE3.txt

profilerDecode0:
		g++ -pg -std=c++11 -o main main.cpp Decoder/Decoder.h Decoder/Decoder.cpp -O0 -pg
		./main decode
		gprof main gmon.out > report.txt
		gcc -c -std=c++11 -g -Wa,-a,-ad main.cpp > testD0.txt

profilerDecode3:
		g++ -pg -std=c++11 -o main main.cpp Decoder/Decoder.h Decoder/Decoder.cpp -O3 -pg
		./main decode
		gprof main gmon.out > report.txt
		gcc -c -std=c++11 -g -Wa,-a,-ad main.cpp > testD3.txt