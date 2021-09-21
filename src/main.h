//
// Created by Guilherme Deconto on 8/25/21.
//

#ifndef VIGENERE_IC_MAIN_H
#define VIGENERE_IC_MAIN_H

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>

class main {

public:
    static int estimateKeyLength(string inputFile, const string& prob);
    static string findKey(string inputFile, int keyLength, const string& prob);
    static char frequencyAnalysis(string text, const string& prob);
    static string decipher(string input, string key);

};

#endif //VIGENERE_IC_MAIN_H
