#include <iostream>
#include "Decoder/Decoder.h"
#include <chrono>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;

    auto d = Decoder();

    auto begin = chrono::high_resolution_clock::now();

    string encodeOrDecode = argv[1];
    const int runsNumber = 1000000;

    if (encodeOrDecode == "encode")
        d.codeBig("Example text", true, runsNumber);    // Encode
    else if (encodeOrDecode == "decode")
        d.codeBig("-...---.-.-.---...-.---...---.---...-.---.---.-...-.---.-.-...-.......---...-...---.-.-.---...---", false, runsNumber);       // Decode

    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000000.0;
    cout << "Worked for " << time << " s" << endl;

//    cout << d.decode("-.-.-...---.---.---...---.---...-.......---...-...---.-.-.---...---") << endl;
    return 0;
}