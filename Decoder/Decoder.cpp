//
// Created by max on 14.09.15.
//

#include "Decoder.h"
#include <algorithm>

Decoder::Decoder() {
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

string Decoder::EncodeOneSymbol(string symbol) {
    if (1 < symbol.length())    // Must be one and only one symbol
        return "";

    // Transforming symbol to uppercase
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);

    // Looking for symbol in alphabet
    for (unsigned int i = 0; i < alphabet.size(); i++)
        if (alphabet[i].symbol == symbol)
            return alphabet[i].code;

    // If didn't find it
    return "";
}

string Decoder::DecodeOneSymbol(string code) {
    // Looking for code in alphabet
    for (unsigned int i = 0; i < alphabet.size(); i++)
        if (alphabet[i].code == code)
            return alphabet[i].symbol;

    // If no such code
    return "";
}

string Decoder::Decode(string code) {
    string result;

    // Split to words
    vector<string> words = Split(code, ".......");  // 7 units
    for (int i = 0; i < words.size(); i++) {
        // Split to letters
        vector<string> letters = Split(words[i], "...");    // 3 units
        for (int j = 0; j < letters.size(); j++)
            result += DecodeOneSymbol(letters[j]);
        if (i + 1 < words.size())   // If not a lats word
            result += ' ';
    }
    return result;
}


string Decoder::Encode(string str) {
    string result;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ')  // Space between words is 7 units
            result += ".......";    // 7 spaces
        else {
            string currentLetter;  // To create string from char
            currentLetter += str[i];
            result += EncodeOneSymbol(currentLetter);

            if (i + 1 < str.length() && str[i + 1] != ' ')  // If not a last letter. Space between letters in 3 units
                result += "...";    // 3 spaces
        }
    }

    return result;
}

vector<string> Decoder::Split(string str, string splitBy) {
    auto res = vector<string>();

    size_t pos;
    while ((pos = str.find(splitBy)) != string::npos) {
        res.push_back(str.substr(0, pos));      // Adding string
        str.erase(0, pos + splitBy.length());  // Deleting it from str
    }
    res.push_back(str);     // Adding last part

    return res;
}

void Decoder::CodeBig(string line, bool encrypt, int numberOfTimes) {
    if (encrypt)
        cout << "I encoded\n\"" << line << "\"\nto\n\"" << Encode(line) << "\"\nAnd will do it " << numberOfTimes - 1 <<
        " more times\n";
    else
        cout << "I decoded\n\"" << line << "\"\nto\n\"" << Decode(line) << "\"\nAnd will do it " << numberOfTimes - 1 <<
        " more times\n";

    for (auto i = 0; i < numberOfTimes - 1; i++)
        if (encrypt)
            Encode(line);
        else
            Decode(line);
}
