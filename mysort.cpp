// Name: Daniel Winn
// Class (CECS 325-02)
// Project Name (Prog 4 - Threads)
// Due Date (11//2025)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <string>

// New includes for multithreading
#include <thread>
#include <mutex>

using namespace std;

int main(int argc, char* argv[]) {
    // Check for 3 arguments in Prog 4 (program, input, output, segments)
    if (argc != 4) {
        cerr << "You must use 3 command line arguements: " << argv[0] << " INPUT OUTPUT" << endl;
        return 1;
    }

    // Store the file names of the input and output
    string input_file = argv[1];
    string output_file = argv[2];

    int num_segments = stoi(argv[3]); // Store segments

    // Dynamic array for counting numbers
    int N = 0;
    int temp_num;
    
    // Opens the input file to read, throws an error if it cannot be opened.
    ifstream countFile(input_file);
    if (!countFile.is_open()) {
        cerr << "Error: Failed to open input file." << endl;
        return 1;
    }

    // Loop that counts every number in the input file
    while (countFile >> temp_num) {
        N++;
    }
    // Closes input file once the while loop finishes
    countFile.close();

    cout << "File has " << N << " numbers." << endl; // Debugging

    int* main_array = new int[N]; // Dynamic array that holds numbers

    // Read the numbers from the input file into the main_array
    ifstream inFile(input_file);
    if (!inFile.is_open()) {
        cerr << "Error: Failed to open input file." << endl;
        delete[] main_array; // Cleans memory before exit
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        inFile >> main_array[i];
    }
    inFile.close();
    cout << "Loaded " << N << " numbers into main_array." << endl; // Debugging

    // Cleanup
    delete[] main_array;
    cout << "Sorting complete. Exiting program." << endl;
    return 0;
}
