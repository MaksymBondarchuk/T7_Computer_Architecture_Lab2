//
// Created by max on 14.09.15.
//

#ifndef T7_COMPUTER_ARCHITECTURE_LAB1_DECODER_H
#define T7_COMPUTER_ARCHITECTURE_LAB1_DECODER_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Decoder {
    // Structure for keeping one Morse symbol
    struct morse_symbol {
        string symbol;
        string code;

        morse_symbol(string symbol, string morse_seq) {
            this->symbol = symbol;
            this->code = morse_seq;
        }
    };

    // International Morse alphabet
    vector<morse_symbol> alphabet;

public:
    Decoder();

    // Decodes one symbol
    string decode_one_symbol(string code);

    // Encodes one symbol
    string encode_one_symbol(string symbol);

    // Decodes sequence of symbols
    string decode(string code);

    // Encodes sequence of symbols
    string encode(string str);

    // Splits string by split_by. Returns vector of strings
    vector<string> split(string str, string split_by);

    // Decrypts/encrypts one file to other
    // if encrypt is true then encrypts else decrypts
    void codeBig(string line, bool encrypt, int numberOfTimes);
};


#endif //T7_COMPUTER_ARCHITECTURE_LAB1_DECODER_H
