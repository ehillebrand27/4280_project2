
#include <iostream>
#include "scanner.h"
#include "token.h"
using namespace std;


void testScanner() {
    token tk;

    while (true) {
        tk = scanner();  

        // Print the token
        cout << tokenNames[tk.id] << " " << tk.instance << " " << tk.line << endl;

        if (tk.id == EOFTk)
            break;
    }
}