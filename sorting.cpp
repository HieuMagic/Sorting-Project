#include "sorting.h"

using namespace std;

// Function pointer type for sorting algorithms and data orders
typedef SortResults (*SortFunction)(int*, int);
typedef void (*DataOrder)(int*, int);

// Map to store the algorithm names and names of the function to call them
unordered_map<string, SortFunction> sorting_algorithms;

// Map to store the data order names and names of the function to generate them
unordered_map<string, DataOrder> data_orders;

int main(int argc, char** argv)
{
    // Add all the data orders and finished algorithms to the maps
    ListAlgorithms();
    ListDataOrder();

    // We will collect data for report if there is only 1 argument, which is only execute the .exe file
    if (argc == 1){
        CollectDataForReport();
        return 0;
    }

    // Get the flag and check if it valid or not to continue
    string flag = argv[1];
    
    if (flag == "-a"){
        // Get the algorithm name
        string algorithm_name = argv[2];

        // Function pointer for the algorithm
        SortFunction sort_function;

        // Point the function pointer
        if (sorting_algorithms.count(algorithm_name) == 0){
            cout << "The algorithm isn't exist in the algorithms list. Ending program...";
            return 1;
        }
        else {
            sort_function = sorting_algorithms[algorithm_name];
        }

        // Knowing what command to run
        if (argc == 5){ // Which is whether command 1 or 3
            // COMMAND 1
            if (!is_number(argv[3])){ // If the 3th-index of argv is not a number, then we run command 1. (argv[3] = [Input filename])
                // Get value from argument
                string filename = argv[3];
                string output_parameter = argv[4];

                // File processing
                ifstream fin(filename);
                if (!fin.is_open()){
                    cout << "Unable to open input file. Ending program...";
                    return 1;
                }
                
                // Extract data from the input file
                string data_line;
                getline(fin, data_line);
                int size = stoi(data_line);
                getline(fin, data_line);
            
                // Since each of the element we need to extract is separated by a single space
                // We will extract the data from the string by using the space as the delimiter
                int data_index = 0;
                int* array = new int[size];
                for (int i = 0; i < size; i++){
                    array[i] = stoi(data_line.substr(data_index, data_line.find(' ', data_index) - data_index));
                    data_index = data_line.find(' ', data_index) + 1;
                }
                
                // Duplicate the array
                int* array_2 = new int[size];
                copy(array, array + size, array_2);

                // Sort the array and get the result
                SortResults result = sort_function(array_2, size);
                
                // Write the sorted array to the output file
                ofstream fout("output.txt");
                if (!fout.is_open()){
                    cout << "Unable to open output file. Ending program...";
                    return 1;
                }
                for (int i = 0; i < size; i++){
                    fout << array_2[i] << " ";
                }

                // Check if we need to show time or number of comparions or both
                bool show_time = false;
                bool show_comparisons = false;
                if (output_parameter == "-time" || output_parameter == "-both") show_time = true;
                if (output_parameter == "-comp" || output_parameter == "-both") show_comparisons = true;

                // Show the results
                cout << "ALGORITHM MODE\n";
                cout << "Algorithm: " << algorithm_name << "\n";
                cout << "Input file: " << filename << '\n';
                cout << "input size: " << size << "\n";
                cout << "----------------------------------\n";
                if (show_time) cout << "Running time: " << result.time_ms << "\n";
                if (show_comparisons) cout << "Comparison: " << result.comparisons << "\n";

                delete[] array;
                delete[] array_2;
                fin.close();
                fout.close();
            }  
            // COMMAND 3
            else {// If argv[3] is a number, then we run command 3 (argv[3] = [Input size])
                // Get data from argurment
                int size = stoi(argv[3]);
                string output_parameter = argv[4];

                // Show the results header
                cout << "ALGORITHM MODE\n";
                cout << "Algorithm: " << algorithm_name << "\n";
                cout << "Input size: " << size << '\n';
                
                // Initialize the input file index
                string input_file_index = "1";

                // For each data order, we print the results
                for (pair<string, DataOrder> data_order : data_orders)
                {
                    // Create the array based on the data_order and size
                    int* array = new int[size];
                    data_order.second(array, size);

                    // Duplicate the array
                    int* array_2 = new int[size];
                    copy(array, array + size, array_2);

                    // Sort the array and get the result
                    SortResults result = sort_function(array_2, size);
                    
                    // Write the generated array to the output file 
                    // (This run 4 times and each time we write to input_1.txt, input_2.txt, input_3.txt, input_4.txt)
                    ofstream fout("input_" + input_file_index + ".txt");
                    if (!fout.is_open()){
                        cout << "Unable to open output file. Ending program...";
                        return 1;
                    }

                    for (int i = 0; i < size; i++){
                        fout << array[i] << " ";
                    }

                    // Increase the input file index
                    input_file_index[0]++;

                    // Check if we need to show time or number of comparions or both
                    bool show_time = false;
                    bool show_comparisons = false;
                    if (output_parameter == "-time" || output_parameter == "-both") show_time = true;
                    if (output_parameter == "-comp" || output_parameter == "-both") show_comparisons = true;

                    cout << "Input order: " << data_order.first << "\n";
                    cout << "----------------------------------\n";
                    if (show_time) cout << "Running time: " << result.time_ms << "\n";
                    if (show_comparisons) cout << "Comparison: " << result.comparisons << "\n";
                    cout << "\n";
                    
                    delete[] array;
                    delete[] array_2;
                    fout.close();
                }
            }
        }
        // COMMAND 2
        else if (argc == 6){ // Which is the command 2's number of arguments. We run command 2
            // Get data from argurment
            int size = stoi(argv[3]);
            string input_order_name = argv[4];
            string output_parameter = argv[5];

            // Function pointer for the data order
            DataOrder order_function;

            // Point the function pointer
            if (data_orders.count(input_order_name) == 0)
            {
                cout << "The data order isn't exist in the data_orders list. Ending program...";
                return 1;
            }
            else
            {
                order_function = data_orders[input_order_name];
            }

            // Create array
            int* array = new int[size];
            order_function(array, size);

            // duplicate the array
            int* array_2 = new int[size];
            copy(array, array + size, array_2);

            // Sort the array and get the result
            SortResults result = sort_function(array_2, size);
            
            // Write the generated array to the input file
            ofstream fout("input.txt");
            if (!fout.is_open()){
                cout << "Unable to open output file. Ending program...";
                return 1;
            }

            for (int i = 0; i < size; i++){
                fout << array[i] << " ";
            }

            // Write the sorted array to the output file
            ofstream fout2("output.txt");
            if (!fout2.is_open()){
                cout << "Unable to open output file. Ending program...";
                return 1;
            }

            for (int i = 0; i < size; i++){
                fout2 << array_2[i] << " ";
            }

            // Check if we need to show time or number of comparions or both
            bool show_time = false;
            bool show_comparisons = false;
            if (output_parameter == "-time" || output_parameter == "-both") show_time = true;
            if (output_parameter == "-comp" || output_parameter == "-both") show_comparisons = true;

            // Show the results
            cout << "ALGORITHM MODE\n";
            cout << "Algorithm: " << algorithm_name << "\n";
            cout << "Input size: " << size << '\n';
            cout << "input order: " << input_order_name << "\n";
            cout << "----------------------------------\n";
            if (show_time) cout << "Running time: " << result.time_ms << "\n";
            if (show_comparisons) cout << "Comparison: " << result.comparisons << "\n";

            delete[] array;
            delete[] array_2;
            fout.close();
            fout2.close();
        }
        else {
            cout << "Too many/few arguments. Ending program...";
            return 1;
        }
    }
    else if (flag == "-c"){
        // Get the algorithm names
        string algorithm_1_name = argv[2];
        string algorithm_2_name = argv[3];

        // Function pointers for the algorithms
        SortFunction sort_function_1;
        SortFunction sort_function_2;

        // Point the function pointers
        if (sorting_algorithms.count(algorithm_1_name) == 0 || sorting_algorithms.count(algorithm_2_name) == 0){
            cout << "The algorithm isn't exist in the algorithms list. Ending program...";
            return 1;
        }
        else {
            sort_function_1 = sorting_algorithms[algorithm_1_name];
            sort_function_2 = sorting_algorithms[algorithm_2_name];
        }

        // COMMAND 4
        if (argc == 5){ // Which is the command 4's number of arguments. We run command 4
            // Get data from argurment
            string filename = argv[4];

            // File processing
            ifstream fin(filename);
            if (!fin.is_open()){
                cout << "Unable to open input file. Ending program...";
                return 1;
            }
            
            // Extracting data from the input file
            string data_line;
            getline(fin, data_line);
            int size = stoi(data_line);
            getline(fin, data_line);
        
            // Since each of the element we need to extract is separated by a single space
            // We will extract the data from the string by using the space as the delimiter
            int data_index = 0;
            int* array = new int[size];
            for (int i = 0; i < size; i++){
                array[i] = stoi(data_line.substr(data_index, data_line.find(' ', data_index) - data_index));
                data_index = data_line.find(' ', data_index) + 1;
            }

            // Duplicate the array
            int* array_2 = new int[size];
            copy(array, array + size, array_2);
            // Sort the array and get the results
            SortResults result_1 = sort_function_1(array_2, size);

            // Duplicate the array again
            copy(array, array + size, array_2);
            // Sort the array and get the results
            SortResults result_2 = sort_function_2(array_2, size);

            // Show the results
            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algorithm_1_name << " | " << algorithm_2_name <<  "\n";
            cout << "Input file: " << filename << '\n';
            cout << "Input size: " << size << "\n";
            cout << "----------------------------------\n";
            cout << "Running time: " << result_1.time_ms << " | " << result_2.time_ms << "\n";
            cout << "Comparison: " << result_1.comparisons << " | " << result_2.comparisons << "\n";

            delete[] array;
            delete[] array_2;
            fin.close();
        }
        // COMMAND 5
        else if (argc == 6){ // Which is the command 5's number of arguments. We run command 5
            // Get data from argurment
            int size = stoi(argv[4]);
            string input_order_name = argv[5];

            // Point the function pointer
            DataOrder order_function;
            if (data_orders.count(input_order_name) == 0)
            {
                cout << "The data order isn't exist in the data_orders list. Ending program...";
                return 1;
            }
            else
            {
                order_function = data_orders[input_order_name];
            }

            // Create array
            int* array = new int[size];
            int* array_2 = new int[size];
            // Generate the array based on the input order
            order_function(array, size);

            // Duplicate the array
            copy(array, array + size, array_2);
            // Sort the array and get the results
            SortResults result_1 = sort_function_1(array_2, size);

            // Duplicate the array again
            copy(array, array + size, array_2);
            // Sort the array and get the results
            SortResults result_2 = sort_function_2(array_2, size);

            // Write the generated array to the input file
            ofstream fout("input.txt");
            if (!fout.is_open()){
                cout << "Unable to open output file. Ending program...";
                return 1;
            }

            for (int i = 0; i < size; i++){
                fout << array[i] << " ";
            }

            // Show the results
            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algorithm_1_name << " | " << algorithm_2_name <<  "\n";
            cout << "Input size: " << size << "\n";
            cout << "Input order: " << input_order_name << "\n";
            cout << "----------------------------------\n";
            cout << "Running time: " << result_1.time_ms << " | " << result_2.time_ms << "\n";
            cout << "Comparison: " << result_1.comparisons << " | " << result_2.comparisons << "\n";

            delete[] array;
            delete[] array_2;
            fout.close();
        }
        else {
            cout << "Too many/few arguments. Ending program...";
            return 1;
        }
    }
    else { // If user enter any other flag
        cout << "Invalid flag. Ending program...";
        return 1;
    }

    return 0;
}

void ListDataOrder(){
    // ADD DATA ORDER HERE
    data_orders["-rev"] = GenerateReverseData;
    data_orders["-sorted"] = GenerateSortedData;
    data_orders["-nsorted"] = GenerateNearlySortedData;
    data_orders["-rand"] = GenerateRandomData;
    // 
}

void ListAlgorithms(){
    // ADD ALGORITHMS HEHE
    sorting_algorithms["selection-sort"] = SelectionSort;
    sorting_algorithms["insertion-sort"] = InsertionSort;
    // sorting_algorithms["shell-sort"] = ShellSort;
    sorting_algorithms["bubble-sort"] = BubbleSort;
    sorting_algorithms["heap-sort"] = HeapSort;
    // sorting_algorithms["merge-sort"] = MergeSort;
    // sorting_algorithms["quick-sort"] = QuickSort;
    sorting_algorithms["radix-sort"] = RadixSort;
    sorting_algorithms["counting-sort"] = CountingSort;
    // sorting_algorithms["binary-insertion-sort"] = BinaryInsertionSort;
    // sorting_algorithms["shaker-sort"] = ShakerSort;
    // sorting_algorithms["flash-sort"] = FlashSort;
    // -------------------------------------
    // Only add algorithms that are fully implemented
}

// Use to check if a string is a number (Support function)
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool IsSorted(const int a[], const int n){
    for (int i = 0; i < n - 1; i++){
        if (a[i] > a[i + 1]) return false;
    }
    return true;
}

void CollectDataForReport(){
    // Declare Data Size
    vector<int> data_sizes = {50000};

    // Write the result (running time and number of comparisons) in a result file
    ofstream fout("report_data.txt");
    if (!fout.is_open()) cout << "Cant open result file.\n";

    // for each Data Order S1
    for (pair<string, DataOrder> data_order : data_orders){
        // for each Data Size S2
        for (int size : data_sizes){
            // - Create an original array A1 with Data Order S1 and Data Size S2
            int* original_array = new int[size];

            // Check if allocation is successful
            if (original_array == nullptr){
                cout << "Memory allocation failed. Ending program...";
                return;
            }

            // Generate the array based on the data order
            data_order.second(original_array, size); // data_order.second is the function to generate data

            // for each Sorting Algorithm S3
            for (pair<string, SortFunction> algorithm : sorting_algorithms){
                cout << "Processing [" << data_order.first << "] with size [" << size << "] using [" << algorithm.first << "]...\n";
                // - Make a duplicate array A2 of the original array A1
                int* duplicated_array = new int[size];
                // Check if allocation is successful
                if (duplicated_array == nullptr){
                    cout << "Memory allocation failed. Ending program...";
                    return;
                }

                copy(original_array, original_array + size, duplicated_array);
                // - Sort array A2 using the Sorting Algorithm S3, while:
                    // + Measuring the running time (in millisecs), and
                    // + Counting the number of comparisons in the algorithm
                SortResults result = algorithm.second(duplicated_array, size); // algorithm.second is the function to sort
                
                // Double check if the array is sorted
                if (IsSorted(duplicated_array, size) == false){
                    cout << "The array is not sorted. Ending program...";
                    return;
                }

                // - Take note of S1, S2, S3, running time and number of comparisons
                fout << "[" << data_order.first << "] with size [" << size << "] using [" << algorithm.first << 
                        "]\t->Time: " << result.time_ms << " milliseconds\t\tComparisons: " << result.comparisons << "\n";
                
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
    for (int i = 0; i < n; i++){
        int min_index = i;
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[min_index]) min_index = j; comparisons++;
        }
        swap(a[i], a[min_index]);
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
    for (int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key){
            a[j + 1] = a[j];
            j--;
            comparisons++;
        }
        comparisons++;
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
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
            }
            comparisons++;
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
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]){
        largest = left;
        comparisons++;
    }
    if (right < n && a[right] > a[largest]){
        largest = right;
        comparisons++;
    }

    if (largest != i){
        swap(a[i], a[largest]);
        Heapify(a, n, largest, comparisons);
    }
}

SortResults HeapSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    for (int i = n / 2 - 1; i >= 0; i--){
        Heapify(a, n, i, comparisons);
    }

    for (int i = n - 1; i > 0; i--){
        swap(a[0], a[i]);
        Heapify(a, i, 0, comparisons);
    }
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults MergeSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults QuickSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING

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
    for(int i = 1; i < n; i++) {
        comparisons += 2;
        if(a[i] > max)
            max = a[i];
        if(a[i] < min)
            min = a[i];
    }

    // Create count array of size (max - min + 1)
    int range = max - min + 1;
    int* count = new int[range]();
    int* output = new int[n];

    // Count occurrences
    for(int i = 0; i < n; i++) {
        count[a[i] - min]++;
    }

    // Calculate cumulative count
    for(int i = 1; i < range; i++) {
        count[i] += count[i-1];
    }

    // Build output array
    for(int i = n-1; i >= 0; i--) {
        output[count[a[i] - min] - 1] = a[i];
        count[a[i] - min]--;
    }

    // Copy back to original array
    for(int i = 0; i < n; i++) {
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
    for(int i = 1; i < n; i++) {
        comparisons += 2;
        if(a[i] > max) max = a[i];
        if(a[i] < min) min = a[i];
    }

    // Shift array to make all numbers positive
    if(min < 0) {
        for(int i = 0; i < n; i++) {
            a[i] -= min;
        }
        max -= min;
    }

    // Create counting array and output array
    vector<int> count(10, 0);
    vector<int> output(n);
    
    // Do counting sort for every digit
    for(int exp = 1; max/exp > 0; exp *= 10) {
        // Clear count array
        fill(count.begin(), count.end(), 0);

        // Store count of occurrences
        for(int i = 0; i < n; i++) {
            count[(a[i]/exp) % 10]++;
        }

        // Change count[i] so that count[i] contains actual
        // position of this digit in output[]
        for(int i = 1; i < 10; i++) {
            count[i] += count[i-1];
        }

        // Build output array
        for(int i = n-1; i >= 0; i--) {
            output[count[(a[i]/exp) % 10] - 1] = a[i];
            count[(a[i]/exp) % 10]--;
        }

        // Copy output array to a[]
        for(int i = 0; i < n; i++) {
            a[i] = output[i];
        }
    }

    // Shift back if we had negative numbers
    if(min < 0) {
        for(int i = 0; i < n; i++) {
            a[i] += min;
        }
    }
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
    
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}

SortResults FlashSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}