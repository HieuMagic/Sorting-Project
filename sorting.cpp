// This is the "sorting" file of the project.
// It will contain all the sorting algorithms and data orders that we will use in the project. As well as the function to generate the report data.

#include "sorting.h"

using namespace std;

// Map to store the algorithm's command, <name, function pointer>
unordered_map<string, AlgorithmInfo> algorithms_map;

// Map to store the data order's command, <name, function pointer>
unordered_map<string, DataOrderInfo> data_orders_map;

// Explaination for map: 
// Since we only know the command that user will input
// I want it to automatically get the name and function pointer from the command

// List all the data orders
void ListDataOrder(){
    // ADD DATA ORDER HERE
    data_orders_map["-rev"] = {"Reversed", GenerateReverseData};
    data_orders_map["-sorted"] = {"Sorted", GenerateSortedData};
    data_orders_map["-nsorted"] = {"Nearly Sorted", GenerateNearlySortedData};
    data_orders_map["-rand"] = {"Randomize", GenerateRandomData};
    // 
}

// List all the algorithms
void ListAlgorithms(){
    // ADD ALGORITHMS HEHE
    algorithms_map["selection-sort"] = {"Selection Sort", SelectionSort};
    algorithms_map["insertion-sort"] = {"Insertion Sort", InsertionSort};
    algorithms_map["shell-sort"] = {"Shell Sort", ShellSort};
    algorithms_map["bubble-sort"] = {"Bubble Sort", BubbleSort}; 
    algorithms_map["heap-sort"] = {"Heap Sort", HeapSort};
    algorithms_map["merge-sort"] = {"Merge Sort", MergeSort};
    algorithms_map["quick-sort"] = {"Quick Sort", QuickSort};
    algorithms_map["radix-sort"] = {"Radix Sort", RadixSort};
    algorithms_map["counting-sort"] = {"Counting Sort", CountingSort};
    algorithms_map["binary-insertion-sort"] = {"Binary Insertion Sort", BinaryInsertionSort};
    algorithms_map["shaker-sort"] = {"Shaker Sort", ShakerSort}; 
    algorithms_map["flash-sort"] = {"Flash Sort", FlashSort};
    // -------------------------------------
    // Only add algorithms that are fully implemented
}

// Use to check if a string is a number (Support function)
bool IsNumber(const std::string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), [](unsigned char c) { return isdigit(c); });
}

// Check if an array is sorted
bool IsSorted(const int* a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) return false;
    }
    return true;
}

// Collect data for the report
void CollectDataForReport(){
    // Declare Data Size
    vector<int> data_sizes = {10000, 30000, 50000, 100000, 300000, 500000};

    // Write the result (running time and number of comparisons) in a result file
    ofstream fout("report_data.txt");
    if (!fout.is_open()) {
        cerr << "Cannot open result file.\n";
        return;
    }

    // for each Data Order S1
    for (pair<string, DataOrderInfo> data_order_info : data_orders_map){
        // Get the data order info
        DataOrderInfo data_order = data_order_info.second;

        // for each Data Size S2
        for (int size : data_sizes){
            // - Create an original array A1 with Data Order S1 and Data Size S2
            int* original_array = new int[size];

            // Check if allocation is successful
            if (!original_array) {
                cerr << "Memory allocation failed. Ending program...";
                // Clean up and return
                fout.close();
                return;
            }

            // Generate the array based on the data order
            data_order.function(original_array, size);

            // for each Sorting Algorithm S3
            for (pair<string, AlgorithmInfo> algorithm_info : algorithms_map){
                // Get the algorithm info
                AlgorithmInfo algorithm = algorithm_info.second;

                // Show the processing message
                cout << "Processing [" << data_order.name << "] with size [" << size << "] using [" << algorithm.name << "]...\n";
                
                // - Make a duplicate array A2 of the original array A1
                int* duplicated_array = new int[size];
                
                // Check if allocation is successful
                if (!duplicated_array) {
                    cerr << "Memory allocation failed. Ending program...";
                    // Clean up and return
                    fout.close();
                    return;
                }

                copy(original_array, original_array + size, duplicated_array);
                // - Sort array A2 using the Sorting Algorithm S3, while:
                    // + Measuring the running time (in millisecs), and
                    // + Counting the number of comparisons in the algorithm
                SortResults result = algorithm.function(duplicated_array, size); // algorithm.second is the function to sort
                
                // Double check if the array is sorted
                if (!IsSorted(duplicated_array, size)) {
                    cerr << "The array is not sorted. Ending program...";
                    delete[] original_array;
                    delete[] duplicated_array;
                    return;
                }

                // - Take note of S1, S2, S3, running time and number of comparisons
                fout << "[" << data_order.name << "] with size [" << size << "] using [" << algorithm.name << 
                        "]\t->Time: " << result.time_ms << " microseconds\t\tComparisons: " << result.comparisons << "\n";
                
                // - Free the memory of A2
                delete[] duplicated_array;
            }
            // - Free the memory of A1
            delete[] original_array;
            // end for
        }
        // end for
    }
    // end for
    fout.close();
}

SortResults SelectionSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    for (int i = 0; ++ comparisons &&  i < n; i++){
        int min_index = i;
        for (int j = i + 1; ++ comparisons &&  j < n; j++){
            if ( ++ comparisons && a[j] < a[min_index]) min_index = j;
        }
        Swap(a[i], a[min_index]);
    }
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults InsertionSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    for (int i = 1; ++ comparisons &&  i < n; i++){
        int key = a[i];
        int j = i - 1;

        while ( ++ comparisons && j >= 0 && ++ comparisons &&  a[j] > key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    // END OF SORTING
    
    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults ShellSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    // ShellSort with diminishing increment gap
    for (int gap = n / 2; ++ comparisons && gap > 0; gap /= 2) {
        for (int i = gap; ++ comparisons && i < n; i++) {
            int temp = a[i];
            int j = i;
            // Perform gapped insertion sort for this gap size
            while ( ++ comparisons && j >= gap && ++ comparisons &&  a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults BubbleSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    for (int i = 0; ++ comparisons &&  i < n - 1; i++) {
        for (int j = 0; ++ comparisons &&  j < n - i - 1; j++) {
            // Swap if elements are in wrong order
            if ( ++ comparisons && a[j] > a[j + 1]) {
                Swap(a[j], a[j + 1]);
            }
        }
    }
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

void Heapify(int a[], int n, int i, long long &comparisons){
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if ( ++ comparisons && left < n && ++ comparisons &&  a[left] > a[largest]) {
        largest = left;
    }
    // If right child is larger than largest so far
    if ( ++ comparisons && right < n && ++ comparisons &&  a[right] > a[largest]) {
        largest = right;
    }
    // If largest is not root
    if (largest != i) {
        Swap(a[i], a[largest]);
        // Recursively heapify the affected sub-tree
        Heapify(a, n, largest, comparisons);
    }
}

SortResults HeapSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; ++ comparisons &&  i >= 0; i--) {
        Heapify(a, n, i, comparisons);
    }
    // One by one extract an element from heap
    for (int i = n - 1; ++ comparisons &&  i > 0; i--) {
        // Move current root to end
        Swap(a[0], a[i]);
        // Call max heapify on the reduced heap
        Heapify(a, i, 0, comparisons);
    }
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

void Merge(int a[], int low, int middle, int high, long long& comparisons) {
    int n1 = middle - low + 1; // Number of elements in left array
    int n2 = high - middle;    // Number of elements in right array

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; ++ comparisons &&  i < n1; i++) {
        leftArr[i] = a[low + i];
    }
    for (int j = 0; ++ comparisons &&  j < n2; j++) {
        rightArr[j] = a[middle + 1 + j];
    }

    int i = 0, j = 0, k = low;
    // Merge left and right arrays back into original array
    while ( ++ comparisons && i < n1 && ++ comparisons &&  j < n2) {
        if ( ++ comparisons && leftArr[i] <= rightArr[j]) {
            a[k++] = leftArr[i++];
        } else {
            a[k++] = rightArr[j++];
        }
    }

    // Copy remaining elements of leftArr if any
    while ( ++ comparisons && i < n1) {
        a[k++] = leftArr[i++];
    }

    // Copy remaining elements of rightArr if any
    while ( ++ comparisons && j < n2) {
        a[k++] = rightArr[j++];
    }

    delete[] leftArr;
    delete[] rightArr;
}

void MergeSort(int a[], int low, int high, long long& comparisons) {
    if ( ++ comparisons && low < high) {
        int middle = low + (high - low) / 2; // Same as (low + high) / 2 but avoids overflow for large low & high

        MergeSort(a, low, middle, comparisons);
        MergeSort(a, middle + 1, high, comparisons);
        Merge(a, low, middle, high, comparisons);
    }
}

SortResults MergeSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    MergeSort(a, 0, n - 1, comparisons);
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}


int FindMedian(int a[], int low, int high, long long& comparisons) {
    int mid = low + (high - low) / 2;
    // Sort the low, mid, high elements
    if ( ++ comparisons && a[low] > a[mid]) swap(a[low], a[mid]);
    if ( ++ comparisons && a[low] > a[high]) swap(a[low], a[high]);
    if ( ++ comparisons && a[mid] > a[high]) swap(a[mid], a[high]);
    // Put the median at the end
    swap(a[mid], a[high]);
    return a[high];
}

int Partition(int a[], int low, int high, long long& comparisons) {
    int pivot = FindMedian(a, low, high, comparisons); // Determine pivot as median of first, middle, last
    int i = low - 1; // Index of smaller element

    for (int j = low; ++ comparisons &&  j < high; j++) {
        if ( ++ comparisons && a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void QuickSort(int a[], int low, int high, long long& comparisons) {
    if ( ++ comparisons && low < high) {
        int pivot = Partition(a, low, high, comparisons);
        // Recursively sort elements before and after partition
        QuickSort(a, low, pivot - 1, comparisons);
        QuickSort(a, pivot + 1, high, comparisons);
    }
}

SortResults QuickSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    QuickSort(a, 0, n - 1, comparisons);
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

void CountingSortHelper(int a[], const int n, int exp, long long &comparisons)
{
    // Find min and max
    int max = a[0], min = a[0];
    for(int i = 1; ++ comparisons &&  i < n; i++) {
        if( ++ comparisons && a[i] > max)
            max = a[i];
        if( ++ comparisons && a[i] < min)
            min = a[i];
    }

    // Create count array of size (max - min + 1)
    int range = max - min + 1;
    int* count = new int[range]();
    int* output = new int[n];

    // Count occurrences
    for(int i = 0; ++ comparisons &&  i < n; i++) {
        count[a[i] - min]++;
    }

    // Calculate cumulative count
    for(int i = 1; ++ comparisons &&  i < range; i++) {
        count[i] += count[i-1];
    }

    // Build output array
    for(int i = n-1; ++ comparisons &&  i >= 0; i--) {
        output[count[a[i] - min] - 1] = a[i];
        count[a[i] - min]--;
    }

    // Copy back to original array
    for(int i = 0; ++ comparisons &&  i < n; i++) {
        a[i] = output[i];
    }

    // Clean up
    delete[] count;
    delete[] output;
}

SortResults CountingSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    CountingSortHelper(a, n, 1, comparisons);
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults RadixSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    // Find min and max
    int max = a[0], min = a[0];
    for(int i = 1; ++ comparisons &&  i < n; i++) {
        if( ++ comparisons && a[i] > max) max = a[i];
        if( ++ comparisons && a[i] < min) min = a[i];
    }

    // Shift array to offset negative values
    if( ++ comparisons && min < 0) {
        for(int i = 0; ++ comparisons &&  i < n; i++) {
            a[i] -= min;
        }
        max -= min;
    }

    // Create counting array and output array
    int* count = new int[10];
    int* output = new int[n];
    
    // Do counting sort for every digit
    for(int exp = 1; ++ comparisons &&  max/exp > 0; exp *= 10) {
        // Clear count array
        fill(count, count + 10, 0);

        // Store count of occurrences
        for(int i = 0; ++ comparisons &&  i < n; i++) {
            count[(a[i]/exp) % 10]++;
        }

        // Change count[i] so that count[i] contains actual
        // position of this digit in output[]
        for(int i = 1; ++ comparisons &&  i < 10; i++) {
            count[i] += count[i-1];
        }

        // Build output array
        for(int i = n-1; ++ comparisons &&  i >= 0; i--) {
            output[count[(a[i]/exp) % 10] - 1] = a[i];
            count[(a[i]/exp) % 10]--;
        }

        // Copy output array to a[]
        for(int i = 0; ++ comparisons &&  i < n; i++) {
            a[i] = output[i];
        }
    }

    // Restore original values if negative shift was applied
    if( ++ comparisons && min < 0) {
        for(int i = 0; ++ comparisons &&  i < n; i++) {
            a[i] += min;
        }
    }
    
    // Clean up
    delete[] count;
    delete[] output;
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults BinaryInsertionSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    for (int i = 1; ++ comparisons &&  i < n; ++i) {
        int key = a[i];
        int left = 0;
        int right = i - 1;

        // Use binary search to find the correct location
        while ( ++ comparisons && left <= right) {
            int mid = left + (right - left) / 2;
            if ( ++ comparisons && a[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Shifting the elements to make space for the key
        for (int j = i - 1; ++ comparisons &&  j >= left; --j) {
            a[j + 1] = a[j];
        }
        a[left] = key;
    }
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults ShakerSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    bool swapped = true;
    int start_index = 0;
    int end_index = n - 1;

    while (swapped) {
        swapped = false;

        // Traverse from left to right
        for (int i = start_index; ++ comparisons &&  i < end_index; ++i) {
            if ( ++ comparisons && a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        // If no elements were swapped, then the array is sorted
        if (!swapped) break;

        // Otherwise, reset the swapped flag so it can be used in the next stage
        swapped = false;
        --end_index;

        // Traverse from right to left
        for (int i = end_index - 1; ++ comparisons &&  i >= start_index; --i) {
            if ( ++ comparisons && a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        ++start_index;
    }
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

void FlashSortHelper(int a[], int n, long long& comparisons) {
    if ( ++ comparisons && n <= 1) return;

    // Find min and max value
    int minVal = a[0], maxVal = a[0];
    for (int i = 1; ++ comparisons &&  i < n; i++) {
        if ( ++ comparisons && a[i] < minVal) minVal = a[i];
        if ( ++ comparisons && a[i] > maxVal) maxVal = a[i];
    }

    // If all elements are the same, return
    if ( ++ comparisons && minVal == maxVal) return;

    // Number of bins used for sorting (at least 2 to avoid division by zero)
    int m = int(0.43 * n) + 1; 
    int* bucket = new (nothrow) int[m](); // Initialize buckets

    if (!bucket) {
        std::cerr << "Memory allocation failed. Exiting sort...\n";
        return;
    }

    // Distribution of elements into buckets
    double c1 = (double)(m - 1) / (maxVal - minVal);
    for (int i = 0; ++ comparisons &&  i < n; i++) {
        int k = int(c1 * (a[i] - minVal));
        bucket[k]++;
    }

    // Compute start index of each bucket
    for (int i = 1; ++ comparisons &&  i < m; i++) {
        bucket[i] += bucket[i - 1];
    }

    // Permutate elements into correct bucket position
    int i = 0;
    while ( ++ comparisons && i < n) {
        int k = int(c1 * (a[i] - minVal));
        if ( ++ comparisons && i >= bucket[k]) {
            i++;
            continue;
        }
        std::swap(a[i], a[--bucket[k]]); // Fix decrement issue in index
    }

    // Apply Insertion Sort for fine-tuning in the sorted range.
    for (int i = 1; ++ comparisons &&  i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        while ( ++ comparisons && j >= 0 && ++ comparisons &&  a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }

    // Clean up the dynamic array
    delete[] bucket;
}

SortResults FlashSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    FlashSortHelper(a, n, comparisons);
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}