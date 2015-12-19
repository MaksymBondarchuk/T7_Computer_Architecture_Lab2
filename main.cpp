#include <iostream>
#include "Decoder/Decoder.h"
#include <algorithm>

using namespace std;
using namespace chrono;

const int runsNumber = 100;


int main(int argc, char **argv) {
    auto d = Decoder();

    cout << "What do you want program to do. [E/d] ";
    string choice;
    cin >> choice;
    transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

    auto timeBegin = high_resolution_clock::now();

    if (choice == "D" || choice == "DECODE")
        d.CodeBig(
                "-.-.-...---.---.---...---.---...-.......-.-.-...-.-.-.-...---.---.---...-.---.-...---.......---...-...---.-.-.---...---",
                false, runsNumber);
    else
        d.CodeBig("Some short text", true, runsNumber);

    auto time = duration_cast<nanoseconds>(high_resolution_clock::now() - timeBegin).count() / 1000000000.0;
    cout << "Worked for " << time << "s" << endl;
    return 0;
}