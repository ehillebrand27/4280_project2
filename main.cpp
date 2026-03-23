
#include <iostream>
#include "scanner.h"
#include "testScanner.h"
using namespace std;


int main(int argc, char* argv[]) {

    //make sure user only inputs two arguments
    if (argc != 2) {
        cout << "Program error file not found" << endl;
        return 1;
    }


    //read input from the second argument
    inFile.open(argv[1]);
    if (!inFile) {
        cout << "Program error file not found" << endl;
        return 1;
    }

    nextChar = getNextChar();

    string filename = argv[1];

    testScanner();

    inFile.close();
    return 0;

}