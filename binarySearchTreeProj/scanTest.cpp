#include "Scanner.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Scanner.h"

using namespace std;
int main(){
    // Characters used in the ASCII art, in order.
    vector<string> chars = {"█","░"};

    // Scanner with 15 lines, 34 characters per line, 2 characters
    Scanner s(15, 34, chars);
    s.dump();
    // Read data files
    if (not s.loadFiles("scrambled.txt", "weights.txt") ) {
        cerr << "Error reading data files." << endl;
    } else {
        s.dump();
        s.inorder();
    }

    if (not s.loadFiles("scrambl.txt", "weight.txt") ) {
        cerr << "Error reading data files." << endl;
    } else {
        s.dump();
        s.inorder();
    }
    return 0;
}