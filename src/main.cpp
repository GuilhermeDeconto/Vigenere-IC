#include "io.h"
#include "main.h"
#include "CoincidenceIndex.h"

using namespace std;

static string alphabet = "abcdefghijklmnopqrstuvwxyz";

static map<char, double> englishProbability = {
        {'a',0.08167}, {'b',0.01492}, {'c',0.02782}, {'d',0.04253}, {'e',0.12702}, {'f',0.02228},
        {'g',0.02015}, {'h',0.06094}, {'i',0.06966}, {'j',0.00153}, {'k',0.00772}, {'l',0.04025},
        {'m',0.02406}, {'n',0.06749}, {'o',0.07507}, {'p',0.01929}, {'q',0.00095}, {'r',0.05987},
        {'s',0.06327}, {'t',0.09056}, {'u',0.02758}, {'v',0.00978}, {'w',0.02360}, {'x',0.00150},
        {'y',0.01974}, {'z',0.00074}};

static map<char, double> portugueseProbability = {
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

    //Ending chrono clock
    auto end = chrono::steady_clock::now();
    //Checking elapsed time
    cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms";

    return 0;
}

int main::estimateKeyLength(string inputFile) {
    double languageIoC = 0.06653846153846153;
    double randomIoC = 0.038461538461538464;

    map<int, double> possibleLength;

    for (int i = 1; i < 100; ++i) {
        string buffer;
        for (int j = 0; j < inputFile.size(); j += i) buffer += inputFile[j];

        double ioc = CoincidenceIndex::calculateIoC(buffer);

        double distanceToLanguageIoC = languageIoC - ioc;
        double distanceToRandomIoC = abs(ioc - randomIoC);

        if (distanceToLanguageIoC < distanceToRandomIoC) {
            possibleLength.insert(std::pair<int, double>(i,ioc));
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