#include "io.h"
#include "main.h"
#include "CoincidenceIndex.h"

using namespace std;

static string alphabet = "abcdefghijklmnopqrstuvwxyz";

static unordered_map<char, double> englishProbability = {
        {'a',0.08167}, {'b',0.01492}, {'c',0.02782}, {'d',0.04253}, {'e',0.12702}, {'f',0.02228},
        {'g',0.02015}, {'h',0.06094}, {'i',0.06966}, {'j',0.00153}, {'k',0.00772}, {'l',0.04025},
        {'m',0.02406}, {'n',0.06749}, {'o',0.07507}, {'p',0.01929}, {'q',0.00095}, {'r',0.05987},
        {'s',0.06327}, {'t',0.09056}, {'u',0.02758}, {'v',0.00978}, {'w',0.02360}, {'x',0.00150},
        {'y',0.01974}, {'z',0.00074}};

static unordered_map<char, double> portugueseProbability = {
        {'a',0.14634}, {'b',0.01043}, {'c',0.03882}, {'d',0.04992}, {'e',0.1257}, {'f',0.01023},
        {'g',0.01303}, {'h',0.00781}, {'i',0.06186}, {'j',0.00397}, {'k',0.00015}, {'l',0.02779},
        {'m',0.04738}, {'n',0.04446}, {'o',0.09735}, {'p',0.02523}, {'q',0.01204}, {'r',0.06530},
        {'s',0.06805}, {'t',0.04336}, {'u',0.03639}, {'v',0.01575}, {'w',0.00037}, {'x',0.00253},
        {'y',0.00006}, {'z',0.0047}};

int main() {
    //Starting chrono clock
    auto start = chrono::steady_clock::now();

    string input = io::getStringFromFile();

    int keyLength = main::estimateKeyLength(input);

    string key = main::findKey(input, keyLength);

    string decryptedText = main::decipher(input, key);

    cout << "Key Length: " << keyLength << endl;
    cout << "Key: " << key << endl;
    cout << decryptedText << endl;

    //Ending chrono clock
    auto end = chrono::steady_clock::now();
    //Checking elapsed time
    cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms";

    return 0;
}

int main::estimateKeyLength(string inputFile) {
    double languageIoC = 0.06653846153846153;
    double randomIoC = 0.038461538461538464;

    unordered_map<int, double> possibleLength;

    int inputFileSize = inputFile.size();

    for (int i = 1; i < 15; ++i) {
        string buffer;
        for (int j = 0; j < inputFileSize; j += i) buffer += inputFile[j];

        double ioc = CoincidenceIndex::calculateIoC(buffer);

        double distanceToLanguageIoC = languageIoC - ioc;
        double distanceToRandomIoC = abs(ioc - randomIoC);

        if (distanceToLanguageIoC < distanceToRandomIoC) {
            possibleLength[i] = ioc;
        }
    }

    double bestIoC;
    int keyLength;

    for(auto const& [key, val] : possibleLength) {
        if(bestIoC < val) {
            bestIoC = val;
            keyLength = key;
        }
    }

    return keyLength;
}

string main::decipher(string input, string key) {
    string decryptedText;

    for (int i = 0; i < input.size(); ++i) {
        int position = (input[i] - key[i % key.length()] + 26) % 26;
        position += 'a';
        char letter = position;
        decryptedText += letter;
    }
    return decryptedText;
}

string main::findKey(string input, int keyLength)
{
    vector<string> text (keyLength);
    string key;

    for (int i = 0; i < input.length(); i++) {
        int position = i % keyLength;
        text[position] += input[i];
    }

    for (int i = 0; i < text.size(); ++i) {
        key += frequencyAnalysis(text[i]);
    }

    return key;
}

char main::frequencyAnalysis(string text)
{
    unordered_map<char, int> lettersFrequency;

    for (int i = 0; i < text.length(); i++) {
        char charAt;
        charAt = text[i];
        if (lettersFrequency.count(charAt)) {
            lettersFrequency[charAt]++;
        } else {
            lettersFrequency[charAt] = 1;
        }
    }

    unordered_map<char, int> chiSquaredDictionary;

    for(int i = 0; i < alphabet.length(); i++) {
        double chiSquared = 0;
        for(auto const& [key, val] : portugueseProbability) {
            int newIndex = alphabet.find(key) + i;
            if (newIndex > 25) {
                newIndex = newIndex - 26;
            }

            if (lettersFrequency.count(alphabet.at(newIndex))) {
                int letterFrequency = lettersFrequency[alphabet.at(newIndex)];
                double mtFreq = portugueseProbability[key] * text.length();
                chiSquared += pow(letterFrequency - mtFreq, 2) / mtFreq;
            }
        }
        chiSquaredDictionary[alphabet.at(i)] =  chiSquared;
    }

    double lowerChiSquared = numeric_limits<double>::infinity();
    char keyLetter = ' ';

    for (auto const& [key, val] : chiSquaredDictionary) {
        if (chiSquaredDictionary[key] < lowerChiSquared ) {
            lowerChiSquared = chiSquaredDictionary[key];
            keyLetter = key;
        }
    }

    return keyLetter;
}