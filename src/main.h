//
// Created by Guilherme Deconto on 8/25/21.
//

#ifndef VIGENERE_IC_MAIN_H
#define VIGENERE_IC_MAIN_H

#include <iostream>
#include <chrono>
#include <string>
#include <cmath>
#include <vector>
#include <cmath>
#include <unordered_map>

class main {

public: static int estimateKeyLength(string inputFile);
public: static string findKey(string file, int keyLength);
public: static char frequencyAnalysis(string text);
public: static string decipher(string input, string key);

};

#endif //VIGENERE_IC_MAIN_H
