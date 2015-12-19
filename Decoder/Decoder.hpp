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
#include <algorithm>

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
    Decoder() {
        alphabet = vector<MorseSymbol>();

        // Letters
        alphabet.push_back(MorseSymbol("A", "-.---"));
        alphabet.push_back(MorseSymbol("B", "---.-.-.-"));
        alphabet.push_back(MorseSymbol("C", "----.-.---.-"));
        alphabet.push_back(MorseSymbol("D", "---.-.-"));
        alphabet.push_back(MorseSymbol("E", "-"));
        alphabet.push_back(MorseSymbol("F", "-.-.---.-"));
        alphabet.push_back(MorseSymbol("G", "---.---.-"));
        alphabet.push_back(MorseSymbol("H", "-.-.-.-"));
        alphabet.push_back(MorseSymbol("I", "-.-"));
        alphabet.push_back(MorseSymbol("J", "-.---.---.---"));
        alphabet.push_back(MorseSymbol("K", "---.-.---"));
        alphabet.push_back(MorseSymbol("L", "-.---.-.-"));
        alphabet.push_back(MorseSymbol("M", "---.---"));
        alphabet.push_back(MorseSymbol("N", "---.-"));
        alphabet.push_back(MorseSymbol("O", "---.---.---"));
        alphabet.push_back(MorseSymbol("P", "-.---.---.-"));
        alphabet.push_back(MorseSymbol("Q", "---.---.-.---"));
        alphabet.push_back(MorseSymbol("R", "-.---.-"));
        alphabet.push_back(MorseSymbol("S", "-.-.-"));
        alphabet.push_back(MorseSymbol("T", "---"));
        alphabet.push_back(MorseSymbol("U", "-.-.---"));
        alphabet.push_back(MorseSymbol("V", "-.-.-.---"));
        alphabet.push_back(MorseSymbol("W", "-.---.---"));
        alphabet.push_back(MorseSymbol("X", "---.-.-.---"));
        alphabet.push_back(MorseSymbol("Y", "---.-.---.---"));
        alphabet.push_back(MorseSymbol("Z", "---.---.-.-"));

        // Numbers
        alphabet.push_back(MorseSymbol("1", "-.---.---.---.---"));
        alphabet.push_back(MorseSymbol("2", "-.-.---.---.---"));
        alphabet.push_back(MorseSymbol("3", "-.-.-.---.---"));
        alphabet.push_back(MorseSymbol("4", "-.-.-.-.---"));
        alphabet.push_back(MorseSymbol("5", "-.-.-.-.-"));
        alphabet.push_back(MorseSymbol("6", "---.-.-.-.-"));
        alphabet.push_back(MorseSymbol("7", "---.---.-.-.-"));
        alphabet.push_back(MorseSymbol("8", "---.---.---.-.-"));
        alphabet.push_back(MorseSymbol("9", "---.---.---.---.-"));
        alphabet.push_back(MorseSymbol("0", "---.---.---.---.---"));

        // Special symbols
        alphabet.push_back(MorseSymbol("\"", "-.---.-.-.---.-"));          // .-..-.
        alphabet.push_back(MorseSymbol("$", "-.-.-.---.-.-.---"));         // ...-..-
        alphabet.push_back(MorseSymbol("'", "-.---.---.---.---.-"));       // .----.
        alphabet.push_back(MorseSymbol("(", "---.-.---.---.-"));           // -.--.
        alphabet.push_back(MorseSymbol(")", "---.-.---.---.-.---"));       // -.--.-
        alphabet.push_back(MorseSymbol("[", "---.-.---.---.-"));           // -.--.
        alphabet.push_back(MorseSymbol("]", "---.-.---.---.-.---"));       // -.--.-
        alphabet.push_back(MorseSymbol("+", "-.---.-.---.-"));             // .-.-.
        alphabet.push_back(MorseSymbol(",", "---.---.-.-.---.---"));       // --..--
        alphabet.push_back(MorseSymbol("-", "---.-.-.-.-.---"));           // -....-
        alphabet.push_back(MorseSymbol(".", "-.---.-.---.-.---"));         // .-.-.-
        alphabet.push_back(MorseSymbol("/", "---.-.-.---.-"));             // -..-.
        alphabet.push_back(MorseSymbol(":", "---.---.---.-.-.-"));         // ---...
        alphabet.push_back(MorseSymbol(";", "---.-.---.-.---.-"));         // -.-.-.
        alphabet.push_back(MorseSymbol("=", "---.-.-.-.---"));             // -...-
        alphabet.push_back(MorseSymbol("?", "-.-.---.---.-.-"));           // ..--..
        alphabet.push_back(MorseSymbol("@", "-.---.---.-.---.-"));         // .--.-.
        alphabet.push_back(MorseSymbol("_", "-.-.---.---.-.---"));         // ..--.-
        alphabet.push_back(MorseSymbol("¶", "-.---.-.---.-.-"));           // .-.-..
        alphabet.push_back(MorseSymbol("!", "---.---.---.-"));             // ---.
    }

    // Decodes one symbol
    string DecodeOneSymbol(string code) {
        // Looking for code in alphabet
        for (auto &item: alphabet)
            if (item.code == code)
                return item.symbol;

        // If no such code
        return "";
    }

    // Encodes one symbol
    string EncodeOneSymbol(string symbol) {
        if (1 < symbol.length())    // Must be one and only one symbol
            return "";

        // Transforming symbol to uppercase
        transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);

        // Looking for symbol in alphabet
        for (auto &item: alphabet)
            if (item.symbol == symbol)
                return item.code;

        // If didn't find it
        return "";
    }

    // Decodes sequence of symbols
    string Decode(string code) {
        string result;

        // Split to words
        auto words = Split(code, ".......");  // 7 units

        _decodedWords.clear();
        for (auto &word: words) {
            // Split to letters
            auto letters = Split(word, "...");    // 3 units
            for (auto& letter: letters)
                result += DecodeOneSymbol(letter);
            result += ' ';
        }

        result = result.substr(0, result.size() - 1);
        return result;
    }

    // Encodes sequence of symbols
    string Encode(string str) {
        string result;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ' ')  // Space between words is 7 units
                result += ".......";    // 7 spaces
            else {
                string currentLetter;  // To create string from char
                currentLetter += str[i];
                result += EncodeOneSymbol(currentLetter);

                if (i + 1 < str.length() &&
                    str[i + 1] != ' ')  // If not a last letter. Space between letters in 3 units
                    result += "...";    // 3 spaces
            }
        }

        return result;
    }

    // Splits string by split_by. Returns vector of strings
    vector<string> Split(string str, string splitBy) {
        auto res = vector<string>();

        size_t pos;
        while ((pos = str.find(splitBy)) != string::npos) {
            res.push_back(str.substr(0, pos));      // Adding string
            str.erase(0, pos + splitBy.length());  // Deleting it from str
        }
        res.push_back(str);     // Adding last part

        return res;
    }

    // Decrypts/encrypts one file to other
    // if encrypt is true then encrypts else decrypts
    void CodeBig(string line, bool encrypt, bool optimisedDecode, int numberOfTimes) {
        if (encrypt)
            cout << "I encoded\n\"" << line << "\"\nto\n\"" << Encode(line) << "\"\nAnd will do it " <<
            numberOfTimes - 1 <<
            " more times\n";
        else {
            cout << (optimisedDecode ? "You selected optimised case" : "You selected old case") << endl;
            cout << "I decoded\n\"" << line << "\"\nto\n\"" << DecodeOptimised(line) << "\"\nAnd will do it " <<
            numberOfTimes - 1 <<
            " more times\n";
        }

        if (encrypt)
            for (auto i = 0; i < numberOfTimes - 1; i++)
                Encode(line);
        else if (optimisedDecode)
            for (auto i = 0; i < numberOfTimes - 1; i++)
                DecodeOptimised(line);
        else
            for (auto i = 0; i < numberOfTimes - 1; i++)
                Decode(line);
    }

private:
    void DecodeWord(string word, int idx) {
        string result;

        auto letters = Split(word, "...");    // 3 units
        for (auto& letter: letters)
            result += DecodeOneSymbol(letter);
        result += ' ';

        pthread_mutex_lock(&MCR1);
        _decodedWords[idx] = result;
//        cout << idx << " received " << word << " and given " << result << endl;
        pthread_mutex_unlock(&MCR1);
    }

    string DecodeOptimised(string code) {
        string result;

        // Split to words
        auto words = Split(code, ".......");  // 7 units

        _decodedWords = vector<string>(words.size());
        threads.clear();
        for (auto i = 0; i < words.size(); i++)
            threads.push_back(thread(&Decoder::DecodeWord, this, words[i], i));

        for (auto &t: threads)
            t.join();

        for (auto &word: _decodedWords)
            result += word;
        result = result.substr(0, result.size() - 1);
        return result;
    }

    vector<thread> threads;
};


#endif
