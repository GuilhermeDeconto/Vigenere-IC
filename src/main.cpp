#include "io.h"
#include "main.h"

int main() {
    //Starting chrono clock
    auto start = chrono::steady_clock::now();

    string input = io::getStringFromFile();
    std::cout << "Hello, World!" << std::endl;


    //Ending chrono clock
    auto end = chrono::steady_clock::now();
    //Checking elapsed time
    cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms";

    return 0;
}
