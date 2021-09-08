#include "io.h"
#include "main.h"
#include "IndexOfCoincidence.h"

using namespace std;

static string alphabet = "abcdefghijklmnopqrstuvwxyz";

static  vector<pair<char, double>> englishProbability = {
        {'a',0.08167}, {'b',0.01492}, {'c',0.02782}, {'d',0.04253}, {'e',0.12702}, {'f',0.02228},
        {'g',0.02015}, {'h',0.06094}, {'i',0.06966}, {'j',0.00153}, {'k',0.00772}, {'l',0.04025},
        {'m',0.02406}, {'n',0.06749}, {'o',0.07507}, {'p',0.01929}, {'q',0.00095}, {'r',0.05987},
        {'s',0.06327}, {'t',0.09056}, {'u',0.02758}, {'v',0.00978}, {'w',0.02360}, {'x',0.00150},
        {'y',0.01974}, {'z',0.00074}};

static vector<pair<char, double>> portugueseProbability = {
        {'a',0.14634}, {'b',0.01043}, {'c',0.03882}, {'d',0.04992}, {'e',0.1257}, {'f',0.01023},
        {'g',0.01303}, {'h',0.00781}, {'i',0.06186}, {'j',0.00397}, {'k',0.00015}, {'l',0.02779},
        {'m',0.04738}, {'n',0.04446}, {'o',0.09735}, {'p',0.02523}, {'q',0.01204}, {'r',0.06530},
        {'s',0.06805}, {'t',0.04336}, {'u',0.03639}, {'v',0.01575}, {'w',0.00037}, {'x',0.00253},
        {'y',0.00006}, {'z',0.0047}};

int main() {
    //Starting chrono clock
    auto start = chrono::steady_clock::now();

    // Read input file
    string input = io::getStringFromFile();

    // Estimate key length
    int keyLength = main::estimateKeyLength(input);

    // Find key
    string key = main::findKey(input, keyLength);

    // Decrypt text
    string decryptedText = main::decipher(input, key);

    cout << "Key Length: " << keyLength << endl;
    cout << "Key: " << key << endl;
    cout << "Decrypted text wrote to output file" << endl;
//    cout << decryptedText << endl;

    // Writing decrypted text to output file
    ofstream out("output.txt");
    out << "Key Length: " << keyLength << endl;
    out << "Key: " << key << endl;
    out << decryptedText << endl;
    out.close();

    //Ending chrono clock
    auto end = chrono::steady_clock::now();
    //Checking elapsed time
    cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms";

    return 0;
}

int main::estimateKeyLength(string inputFile) {
    double languageIoC = 0.06653846153846153;
    double randomIoC = 0.038461538461538464;
    // Maximum guessed key length
    int maxKeyLenght = 15;

    // Declaring vector of pairs
    vector<pair<int, double>> possibleLength;

    int inputFileSize = inputFile.size();

    // Declaring OpenMP directives in order to improve performance with multithreading
    // pragma omp directive will split the work among all available threads in host system and,
    // after work is done, it'll merge the results from all threads using reduction clause.
    // Shared directive dictates which variables are shared between threads
    #pragma omp declare reduction (merge : vector<pair<int, double>> : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))
    #pragma omp parallel for default(none) shared(inputFileSize, inputFile, languageIoC, randomIoC, maxKeyLenght) reduction(merge:possibleLength)
    for (int i = 1; i < maxKeyLenght; ++i) {
        // Creating a buffer string with every n chars from input file
        string buffer;

        for (int j = 0; j < inputFileSize; j += i) buffer += inputFile[j];

        // Calculating the index of coincidence
        double ioc = IndexOfCoincidence::calculateIoC(buffer);

        // Calculating distances
        double distanceToLanguageIoC = languageIoC - ioc;
        double distanceToRandomIoC = abs(ioc - randomIoC);

        // Checking for a better fit and adding it to my vector of pairs
        if (distanceToLanguageIoC < distanceToRandomIoC) {
            possibleLength.emplace_back(i, ioc);
        }
    }

    // Declaring variables
    double bestIoC;
    int keyLength;

    // Iterating the vector and looking for the lowes IoC
    for(auto const& [key, val] : possibleLength) {
        if(bestIoC < val) {
            bestIoC = val;
            keyLength = key;
        }
    }

    // Returning the char with lowest IoC
    return keyLength;
}

string main::decipher(string input, string key) {
    string decryptedText;

    // Declaring OpenMP directive for parallel processing of for loop
    // Shared variables are: input and key
    // After work is done OpenMP will join results in decryptedText variable
    #pragma omp parallel for default(none) shared(input, key) reduction(+:decryptedText)
    for (int i = 0; i < input.size(); ++i) {
        // Decrypt input file using the key found previously
        int position = (input[i] - key[i % key.length()] + 26) % 26;
        position += 'a';
        char letter = position;
        decryptedText += letter;
    }
    return decryptedText;
}

string main::findKey(string input, int keyLength)
{
    // Declaring variables
    vector<string> text (keyLength);
    string key;

    // Adding each char to their respective position in vector
    for (int i = input.length(); i--;) {
        int position = i % keyLength;
        text[position] += input[i];
    }

    // Declaring OpenMP directive for parallel processing of for loop
    #pragma omp parallel for default(none) shared(text) reduction(+:key)
    for (int i = 0; i < text.size(); ++i) {
        // Finding the key in each row in vector
        key += frequencyAnalysis(text[i]);
    }

    return key;
}

char main::frequencyAnalysis(string text)
{
    // Declaring vector of pairs
    vector<pair<char, int>> lettersFrequency;

    // Looping through the text
    for (int i = text.length(); i--;) {
        char charAt;
        charAt = text[i];
        // Checking if char exists in lettersFrequency vector of pairs
        auto letterFound = find_if(lettersFrequency.begin(), lettersFrequency.end(), [&](pair<char, int> const & ref) {
            return ref.first == charAt;
        });
        if (letterFound != lettersFrequency.end()) {
            // If letter exists, add 1 to its value
            letterFound->second++;
        } else {
            // If letter doesn't exist, insert in vector
            lettersFrequency.emplace_back(charAt, 1);
        }
    }

    // Declaring chi squared vector
    vector<pair<char, int>> chiSquaredVec;

    // Looping through alphabet (a,b,c,d...)
    for(int i = alphabet.length(); i--;) {
        double chiSquared = 0;
        for(auto const& [key, val] : englishProbability) {
            // Calculating the shifted letter
            int newIndex = alphabet.find(key) + i;
            if (newIndex > 25) {
                newIndex = newIndex - 26;
            }
            auto test = find_if(lettersFrequency.begin(), lettersFrequency.end(), [&](pair<char, int> const & ref) {
                return ref.first == alphabet.at(newIndex);
            });
            // If letter is found, calculate its frequency
            if (test != lettersFrequency.end()) {
                int letterFrequency = test->second;
                double mtFreq = val * text.length();
                // Calculating the chi squared
                chiSquared += pow(letterFrequency - mtFreq, 2) / mtFreq;
            }
        }
        // Adding chi squared value for each letter to vector
        chiSquaredVec.emplace_back(alphabet.at(i), chiSquared);
    }

    // Declaring variables
    double lowerChiSquared = numeric_limits<double>::infinity();
    char keyLetter = ' ';

    // Check vector for the lowest chi squared value
    for (auto const& [key, val] : chiSquaredVec) {
        if (val < lowerChiSquared ) {
            lowerChiSquared = val;
            keyLetter = key;
        }
    }

    // Return the letter with the lowest chi squared
    return keyLetter;
}