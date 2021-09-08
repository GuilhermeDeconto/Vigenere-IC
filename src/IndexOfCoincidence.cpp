//
// Created by Guilherme Deconto on 8/26/21.
//

#include <vector>
#include "IndexOfCoincidence.h"

static string alphabet = "abcdefghijklmnopqrstuvwxyz";

double IndexOfCoincidence::calculateIoC(const string& input) {

    // Declaring variables
    vector<pair<char, int>> occurrences;
    int inputSize = input.size();

    // Looping through the string and counting the occurrence of each char
    for (char letter: input) {

        // Checking if letter exists in occurrences vector of pairs
        auto letterFound = find_if(occurrences.begin(), occurrences.end(), [&](pair<char, int> const & ref) {
            return ref.first == letter;
        });
        if (letterFound != occurrences.end()) {
            // If letter exists, add 1 to its value
            letterFound->second += 1;
        }else {
            // If letter doesn't exist, insert in vector
            occurrences.emplace_back(letter, 1);
        }
    }

    double totalSum = 0.0;
    // Loop through alphabet (a,b,c,d...)
    for (char letter: alphabet) {
        // Checking if letter exists in occurrences vector of pairs
        auto letterFound = find_if(occurrences.begin(), occurrences.end(), [&](pair<char, int> const & ref) {
            return ref.first == letter;
        });

        // Checking if letter doesn't exist in vector
        if (letterFound == occurrences.end()) continue;

        // Getting letter occurrence count in string and summing
        int occurrenceCount = letterFound->second;
        double letterIncidence = (occurrenceCount - 1.0) * occurrenceCount;

        totalSum += letterIncidence;
    }

    // Calculating the IoC
    double ioc = totalSum / (inputSize * (inputSize - 1.0));

    // Returning the IoC
    return ioc;
}
