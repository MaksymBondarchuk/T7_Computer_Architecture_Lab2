#include <iostream>
#include "Decoder/Decoder.hpp"


using namespace std;
using namespace chrono;

const int runsNumber = 100;


int main(int argc, char **argv) {
    auto d = Decoder();

    cout << "What do you want program to do? [E/d] ";
    string choice;
    cin >> choice;
    transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

    auto timeBegin = high_resolution_clock::now();

    if (choice == "D" || choice == "DECODE") {
        cout << "You selected decode" << endl;
        cout << "Do you want run optimised case? [y/N] ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

        auto stringForDecode = "-.---.---...---.---.---...-.---.-...---.-.-...-.---.---.---.---......."
                "-.---.---...---.---.---...-.---.-...---.-.-...-.-.---.---.---......."
                "-.---.---...---.---.---...-.---.-...---.-.-...-.-.-.---.---......."
                "-.---.---...---.---.---...-.---.-...---.-.-...-.-.-.-.---......."
                "-.---.---...---.---.---...-.---.-...---.-.-...-.-.-.-.-......."
                "-.---.---...---.---.---...-.---.-...---.-.-...---.-.-.-.-......."
                "-.---.---...---.---.---...-.---.-...---.-.-...---.---.-.-.-......."
                "-.---.---...---.---.---...-.---.-...---.-.-...---.---.---.-.-......."
                "-.---.---...---.---.---...-.---.-...---.-.-...---.---.---.---.-......."
                "-.---.---...---.---.---...-.---.-...---.-.-...-.---.---.---.---...---.---.---.---.---";

        d.CodeBig(stringForDecode, false, (choice == "Y" || choice == "YES"), runsNumber);
    }
    else {
        cout << "You selected encode" << endl;
        d.CodeBig("WORD1 WORD2 WORD3 WORD4 WORD5 WORD6 WORD7 WORD8 WORD9 WORD10", true, false, runsNumber);
    }

    auto time = duration_cast<nanoseconds>(high_resolution_clock::now() - timeBegin).count() / 1000000000.0;
    cout << "Worked for " << time << "s" << endl;
    return 0;
}