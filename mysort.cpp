// Name: Daniel Winn
// Class (CECS 325-02)
// Project Name (Prog 2 - Sort Contest)
// Due Date (10/09/2025)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Declares the bubble sort function
vector<int> bubble(vector<int> v);

int main(int argc, char* argv[]) {
    // Checks if 2 command line arguements are used, throws an error if not.
    // NOTE: `./mysort numbers.dat mysort.out` is technically 3 arguments, so argc must = 3
    if (argc != 3) {
        cerr << "You must use 2 command line arguements: " << argv[0] << " INPUT OUTPUT" << endl;
        return 1;
    }

    // Store the file names of the input and output
    string input_file = argv[1];
    string output_file = argv[2];

    // The vector in which we will store numbers, with a temporary int `num` to hold numbers as they're read.
    vector<int> numbers;
    int num;
    
    // Opens the input file to read, throws an error if it cannot be opened.
    ifstream inFile(input_file);
    if (!inFile.is_open()) {
        cerr << "Error: Failed to open input file." << endl;
        return 1;
    }

    // Adds numbers from the file to the vector as they're read.
    while (inFile >> num) {
        numbers.push_back(num);
    }
    // Closes input file once the while loop finishes
    inFile.close();

    // Calls the bubble function to be stored in a vector "sorted_numbers".
    vector<int> sorted_numbers = bubble(numbers);

    // Opens the output file to write, throws an error if it cannot be opened.
    ofstream outFile(output_file);
    if (!outFile.is_open()) {
        cerr << "Error: Failed to open output file." << endl;
        return 1;
    }
    // Close the output file once written
    outFile.close();

    return 0;
}

// The bubble sort function.
vector<int> bubble(vector<int> v) {
    int n = v.size();
    bool swapped;

    // Outer loop (passes)
    for (int i=0; i<n-1; ++i) {
        swapped = false;

        // Inner loop (comparisons)
        for (int j=0; j<n-i-1; ++j) {
            // Swaps elements if they're in the wrong order.
            if (v[j] > v[j+1]) {
                swap(v[j], v[j+1]);
                swapped = true;
            }
        }
        // Breaks the loop if no two elements were swapped in the inner loop (meaning it's sorted).
        if (swapped == false) {
            break;
        }
    }
    // Returns the sorted vector.
    return v;
}