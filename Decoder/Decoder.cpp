//
// Created by max on 14.09.15.
//

#include "Decoder.h"
#include <algorithm>

Decoder::Decoder() {
    alphabet = vector<morse_symbol>();

    // Letters
    alphabet.push_back(morse_symbol("A", "-.---"));
    alphabet.push_back(morse_symbol("B", "---.-.-.-"));
    alphabet.push_back(morse_symbol("C", "----.-.---.-"));
    alphabet.push_back(morse_symbol("D", "---.-.-"));
    alphabet.push_back(morse_symbol("E", "-"));
    alphabet.push_back(morse_symbol("F", "-.-.---.-"));
    alphabet.push_back(morse_symbol("G", "---.---.-"));
    alphabet.push_back(morse_symbol("H", "-.-.-.-"));
    alphabet.push_back(morse_symbol("I", "-.-"));
    alphabet.push_back(morse_symbol("J", "-.---.---.---"));
    alphabet.push_back(morse_symbol("K", "---.-.---"));
    alphabet.push_back(morse_symbol("L", "-.---.-.-"));
    alphabet.push_back(morse_symbol("M", "---.---"));
    alphabet.push_back(morse_symbol("N", "---.-"));
    alphabet.push_back(morse_symbol("O", "---.---.---"));
    alphabet.push_back(morse_symbol("P", "-.---.---.-"));
    alphabet.push_back(morse_symbol("Q", "---.---.-.---"));
    alphabet.push_back(morse_symbol("R", "-.---.-"));
    alphabet.push_back(morse_symbol("S", "-.-.-"));
    alphabet.push_back(morse_symbol("T", "---"));
    alphabet.push_back(morse_symbol("U", "-.-.---"));
    alphabet.push_back(morse_symbol("V", "-.-.-.---"));
    alphabet.push_back(morse_symbol("W", "-.---.---"));
    alphabet.push_back(morse_symbol("X", "---.-.-.---"));
    alphabet.push_back(morse_symbol("Y", "---.-.---.---"));
    alphabet.push_back(morse_symbol("Z", "---.---.-.-"));

    // Numbers
    alphabet.push_back(morse_symbol("1", "-.---.---.---.---"));
    alphabet.push_back(morse_symbol("2", "-.-.---.---.---"));
    alphabet.push_back(morse_symbol("3", "-.-.-.---.---"));
    alphabet.push_back(morse_symbol("4", "-.-.-.-.---"));
    alphabet.push_back(morse_symbol("5", "-.-.-.-.-"));
    alphabet.push_back(morse_symbol("6", "---.-.-.-.-"));
    alphabet.push_back(morse_symbol("7", "---.---.-.-.-"));
    alphabet.push_back(morse_symbol("8", "---.---.---.-.-"));
    alphabet.push_back(morse_symbol("9", "---.---.---.---.-"));
    alphabet.push_back(morse_symbol("0", "---.---.---.---.---"));

    // Special symbols
    alphabet.push_back(morse_symbol("\"", "-.---.-.-.---.-"));          // .-..-.
    alphabet.push_back(morse_symbol("$", "-.-.-.---.-.-.---"));         // ...-..-
    alphabet.push_back(morse_symbol("'", "-.---.---.---.---.-"));       // .----.
    alphabet.push_back(morse_symbol("(", "---.-.---.---.-"));           // -.--.
    alphabet.push_back(morse_symbol(")", "---.-.---.---.-.---"));       // -.--.-
    alphabet.push_back(morse_symbol("[", "---.-.---.---.-"));           // -.--.
    alphabet.push_back(morse_symbol("]", "---.-.---.---.-.---"));       // -.--.-
    alphabet.push_back(morse_symbol("+", "-.---.-.---.-"));             // .-.-.
    alphabet.push_back(morse_symbol(",", "---.---.-.-.---.---"));       // --..--
    alphabet.push_back(morse_symbol("-", "---.-.-.-.-.---"));           // -....-
    alphabet.push_back(morse_symbol(".", "-.---.-.---.-.---"));         // .-.-.-
    alphabet.push_back(morse_symbol("/", "---.-.-.---.-"));             // -..-.
    alphabet.push_back(morse_symbol(":", "---.---.---.-.-.-"));         // ---...
    alphabet.push_back(morse_symbol(";", "---.-.---.-.---.-"));         // -.-.-.
    alphabet.push_back(morse_symbol("=", "---.-.-.-.---"));             // -...-
    alphabet.push_back(morse_symbol("?", "-.-.---.---.-.-"));           // ..--..
    alphabet.push_back(morse_symbol("@", "-.---.---.-.---.-"));         // .--.-.
    alphabet.push_back(morse_symbol("_", "-.-.---.---.-.---"));         // ..--.-
    alphabet.push_back(morse_symbol("¶", "-.---.-.---.-.-"));           // .-.-..
    alphabet.push_back(morse_symbol("!", "---.---.---.-"));             // ---.
}

string Decoder::encode_one_symbol(string symbol) {
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

string Decoder::decode_one_symbol(string code) {
    // Looking for code in alphabet
    for (unsigned int i = 0; i < alphabet.size(); i++)
        if (alphabet[i].code == code)
            return alphabet[i].symbol;

    // If no such code
    return "";
}

string Decoder::decode(string code) {
    string result;

    // Split to words
    vector<string> words = split(code, ".......");  // 7 units
    for (int i = 0; i < words.size(); i++) {
        // Split to letters
        vector<string> letters = split(words[i], "...");    // 3 units
        for (int j = 0; j < letters.size(); j++)
            result += decode_one_symbol(letters[j]);
        if (i + 1 < words.size())   // If not a lats word
            result += ' ';
    }
    return result;
}


string Decoder::encode(string str) {
    string result;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ')  // Space between words is 7 units
            result += ".......";    // 7 spaces
        else {
            string current_letter;  // To create string from char
            current_letter += str[i];
            result += encode_one_symbol(current_letter);

            if (i + 1 < str.length() && str[i + 1] != ' ')  // If not a last letter. Space between letters in 3 units
                result += "...";    // 3 spaces
        }
    }

    return result;
}

vector<string> Decoder::split(string str, string split_by) {
    vector<string> res = vector<string>();

    size_t pos;
    while ((pos = str.find(split_by)) != string::npos) {
        res.push_back(str.substr(0, pos));      // Adding string
        str.erase(0, pos + split_by.length());  // Deleting it from str
    }
    res.push_back(str);     // Adding last part

    return res;
}

void Decoder::codeBig(string line, bool encrypt, int numberOfTimes) {
    if (encrypt)
        cout << "I encoded\n\"" << line << "\"\nto\n\"" << encode(line) << "\"\nAnd will do it " << numberOfTimes - 1 <<
        " more times\n";
    else
        cout << "I decoded\n\"" << line << "\"\nto\n\"" << decode(line) << "\"\nAnd will do it " << numberOfTimes - 1 <<
        " more times\n";

    for (auto i = 0; i < numberOfTimes - 1; i++)
        if (encrypt)
            encode(line);
        else
            decode(line);
}
