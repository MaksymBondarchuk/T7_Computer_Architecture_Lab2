#include <iostream>
#include "Decoder/Decoder.h"
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;

    auto d = Decoder();

    auto begin = high_resolution_clock::now();

    string encodeOrDecode = argv[1];
    const int runsNumber = 1000;

    if (encodeOrDecode == "encode")
        d.CodeBig("12345", true, runsNumber);
    else if (encodeOrDecode == "decode")
        d.CodeBig("-.---.---.---.---...-.-.---.---.---...-.-.-.---.---...-.-.-.-.---...-.-.-.-.-", false, runsNumber);

    auto end = high_resolution_clock::now();
    auto time = duration_cast<nanoseconds>(end - begin).count() / 1000000000.0;
    cout << "Worked for " << time << " s" << endl;
    return 0;
}