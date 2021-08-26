//
// Created by Guilherme Deconto on 8/26/21.
//

#include "CoincidenceIndex.h"

static string alphabet = "abcdefghijklmnopqrstuvwxyz";

double CoincidenceIndex::calculateIoC(const string& input) {
    map<char, int> occurrences;

    for (char letter: input) {
        if (occurrences.count(letter) != 0) {
            occurrences[letter] += 1;
        }else {
            occurrences[letter] = 1;
        }
    }

    double totalSum = 0.0;
    for (char letter: alphabet) {
        if (occurrences.count(letter) == 0) continue;

        int occurrenceCount = occurrences[letter];
        double letterIncidence = (occurrenceCount - 1.0) * occurrenceCount;

        totalSum += letterIncidence;
    }

    double ioc = totalSum / (input.size() * (input.size() - 1.0));

    return ioc;
}
