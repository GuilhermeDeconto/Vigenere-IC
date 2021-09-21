//
// Created by Guilherme Deconto on 8/25/21.
//

#include "io.h"

string io::getStringFromFile(const string& path)
{
    ifstream inFile;

    //Opening the input file
    //inFile.open("resources/cipher31.txt");
    if (!path.empty()){
        inFile.open(path);
    }else{
        std::cout << "No input file provided, will use bundled cipherenglish.txt" << std::endl;
        inFile.open("resources/cipherenglish.txt");
    }

    stringstream strStream;
    //Reading file
    strStream << inFile.rdbuf();

    //Returning the file content
    return strStream.str();
}
