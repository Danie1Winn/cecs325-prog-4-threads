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
#include <algorithm>

// New includes for multithreading
#include <thread>
#include <mutex>

using namespace std;

// Struct to hold array data
struct Segment {
    int* start; // Pointer to the first element in the segment
    int size; // Number of elements in the segment
};

// Global variable that holds the total swap count
unsigned long long global_swap_count = 0;
mutex swap_mutex;

// Bubble sort function with threading
void bubble(int* arr_ptr, int size, string name) {
    unsigned long long local_swaps = 0;
    bool swapped;

    // Sorting logic with pointer and size
    for (int i=0; i < size - 1; ++i) {
        swapped = false;
        for (int j=0; j < size - i - 1; ++j) {
            // Compares elements
            if (arr_ptr[j] > arr_ptr[j+1]) {
                swap(arr_ptr[j], arr_ptr[j+1]);
                swapped = true;
                local_swaps++;
            }
        }
        if (swapped == false) {
            break;
        }
    }

    // Lock mutex
    swap_mutex.lock();
    cout << "Thread" << name << " completed w/ " << local_swaps << " swaps." << endl;

    global_swap_count += local_swaps;
    swap_mutex.unlock();
}

// Merge sorted array segments into destination array
void merge(int* left, int left_size, int* right, int right_size, int* dest) {
    int i = 0; // Left
    int j = 0; // Right
    int k = 0; // Destination
    
    // Compare
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            dest[k] = left[i];
            i++;
        } else {
            dest[k] = right[j];
            j++;
        }
        k++;
    }

    // Remaining left
    while (i < left_size) {
        dest[k] = left[i];
        i++;
        k++;
    }

    // Remaining right
    while (j < right_size) {
        dest[k] = right[j];
        j++;
        k++;
    }
}

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

    // Dynamic array, holds all segment structs
    Segment* segments = new Segment[num_segments];

    int base_size = N / num_segments;
    int remainder = N % num_segments;
    int* current_ptr = main_array; // Beginning of array

    cout << "Calculating Segemnts" << endl; // Debugging

    // Loop and define segments
    for (int i = 0; i < num_segments; ++i) {
        int segment_size = base_size;
        if (i < remainder) {
            segment_size ++; // Add to the remainder number of segments
        }

        // Distributes remainder by adding it to the last segment
        if (i == num_segments - 1) {
            segment_size += remainder;
        }

        segments[i].start = current_ptr;
        segments[i].size = segment_size;

        current_ptr += segment_size;
    }

    // Dynamic array
    thread* threads = new thread[num_segments];

    // Start threads
    cout << "Launching " << num_segments << " threads." << endl; // Debugging
    for (int i = 0; i < num_segments; ++i) {
        string thread_name = "T" + to_string(i);

        threads[i] = thread(bubble, segments[i].start, segments[i].size, thread_name);
    }

    cout << "Waiting for threads" << endl; // Debugging
    for (int i = 0; i < num_segments; ++i) {
        threads[i].join();
    }

    cout << "Totals swaps from threads: " << global_swap_count << endl; // Debugging

    cout << "Starting merge sort" << endl; // Debugging 

    // Temporary bufers
    int* buffer_a = new int[N];
    int* buffer_b = new int[N];

    copy(segments[0].start, segments[0].start + segments[0].size, buffer_a);

    int current_merged_size = segments[0].size;
    int* source = buffer_a; // Read from
    int* dest = buffer_b; // Write to

    // Loop through segments and  merge
    for (int i = 1; i < num_segments; ++i) {
        merge(source, current_merged_size, segments[i].start, segments[i].size, dest);
        
        // Update size
        current_merged_size += segments[i].size;

        // Swap buffers
        swap(source, dest);
    }

    copy(source, source + N, main_array);
    
    // Cleanup
    delete[] buffer_a;
    delete[] buffer_b;
    delete[] threads;
    delete[] segments;
    delete[] main_array;
    cout << "Sorting complete. Exiting program." << endl;

    return 0;
}
