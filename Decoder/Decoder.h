//
// Created by max on 14.09.15.
//

#ifndef T7_COMPUTER_ARCHITECTURE_LAB1_DECODER_H
#define T7_COMPUTER_ARCHITECTURE_LAB1_DECODER_H

#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include <mutex>

using namespace std;

class Decoder {
    // Structure for keeping one Morse symbol
    struct MorseSymbol {
        string symbol;
        string code;

        MorseSymbol(string symbol, string morseSequence) {
            this->symbol = symbol;
            this->code = morseSequence;
        }
    };

    // International Morse alphabet
    vector<MorseSymbol> alphabet;

    // For improved part
    vector<string> _decodedWords = vector<string>();
    pthread_mutex_t MCR1 = PTHREAD_MUTEX_INITIALIZER;

public:
    Decoder();

    // Decodes one symbol
    string DecodeOneSymbol(string code);

    // Encodes one symbol
    string EncodeOneSymbol(string symbol);

    // Decodes sequence of symbols
    string Decode(string code);

    // Encodes sequence of symbols
    string Encode(string str);

    // Splits string by split_by. Returns vector of strings
    vector<string> Split(string str, string splitBy);

    // Decrypts/encrypts one file to other
    // if encrypt is true then encrypts else decrypts
    void CodeBig(string line, bool encrypt, int numberOfTimes);

    void* DecodeWord(void* word);

    string DecodeOptimised(string code);
};


#endif //T7_COMPUTER_ARCHITECTURE_LAB1_DECODER_H
