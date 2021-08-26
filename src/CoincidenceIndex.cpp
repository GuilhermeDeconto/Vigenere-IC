//
// Created by Guilherme Deconto on 8/26/21.
//

#include <vector>
#include "CoincidenceIndex.h"

static string alphabet = "abcdefghijklmnopqrstuvwxyz";

double CoincidenceIndex::calculateIoC(const string& input) {
    vector<pair<char, int>> occurrences;

    int inputSize = input.size();
    for (char letter: input) {
        auto test = find_if(occurrences.begin(), occurrences.end(), [&](pair<char, int> const & ref) {
            return ref.first == letter;
        });
        if (test != occurrences.end()) {
            test->second += 1;
        }else {
            occurrences.emplace_back(letter, 1);
        }
    }

    double totalSum = 0.0;
    for (char letter: alphabet) {
        auto test = find_if(occurrences.begin(), occurrences.end(), [&](pair<char, int> const & ref) {
            return ref.first == letter;
        });
        if (test == occurrences.end()) continue;

        int occurrenceCount = test->second;
        double letterIncidence = (occurrenceCount - 1.0) * occurrenceCount;

        totalSum += letterIncidence;
    }
    double ioc = totalSum / (inputSize * (inputSize - 1.0));

    return ioc;
}
