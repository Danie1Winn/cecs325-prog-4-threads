// Name: Daniel Winn
// Class (CECS 325-02)
// Project Name (Prog 2 - Sort Contest)
// Due Date (10/09/2025)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    // Checks if 3 command line arguements are used, throws an error if not.
    // NOTE: `generate x -x x` is technically 4 arguments, so argc must = 4
    if (argc != 4) {
        cerr << "You must use 3 command line arguements: " << argv[0] << " COUNT MIN MAX" << endl;
        return 1;
    }

    // Convert all arguments from strings to integers
    int count = stoi(argv[1]);
    int min = stoi(argv[2]);
    int max = stoi(argv[3]);
    
    // C++ random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);

    // Opens numbers.dat
    ofstream outFile("numbers.dat");

    // Uses <fstream> is_open to check if numbers.dat was successfully opened
    if (!outFile.is_open()) {
        cerr << "Error: Failed to open numbers.dat" << endl;
        return 1;
    }

    // Loops for argument "count" # of times
    for (int i=0; i<count; ++i) {
        // Generates 1x random number per loop using our C++ random number generator
        int random_num = distrib(gen);
        // Write the number to numbers.dat followed by a newline
        outFile << random_num << endl;
    }

    // Closes numbers.dat after loop completes
    outFile.close();
    return 0;
}