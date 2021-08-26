//
// Created by Guilherme Deconto on 8/25/21.
//

#ifndef VIGENERE_IC_MAIN_H
#define VIGENERE_IC_MAIN_H

#include <iostream>
#include <chrono>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <cmath>

class main {

public: static int estimateKeyLength(string inputFile);
public: static vector<string> findKey(string file, int keyLength);

};

#endif //VIGENERE_IC_MAIN_H
