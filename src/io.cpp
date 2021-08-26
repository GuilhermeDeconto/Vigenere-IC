//
// Created by Guilherme Deconto on 8/25/21.
//

#include "io.h"

string io::getStringFromFile()
{
    ifstream inFile;

    //Opening the input file
//    inFile.open("resources/cipher31.txt");
    inFile.open("resources/20201-teste2.txt");

    stringstream strStream;
    //Reading file
    strStream << inFile.rdbuf();

    //Returning the file content
    return strStream.str();
}
