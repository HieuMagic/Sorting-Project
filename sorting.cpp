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
    // algorithms_map["shell-sort"] = {"Shell Sort", ShellSort};
    algorithms_map["bubble-sort"] = {"Bubble Sort", BubbleSort}; 
    algorithms_map["heap-sort"] = {"Heap Sort", HeapSort};
    // algorithms_map["merge-sort"] = {"Merge Sort", MergeSort};
    // algorithms_map["quick-sort"] = {"Quick Sort", QuickSort};
    algorithms_map["radix-sort"] = {"Radix Sort", RadixSort};
    algorithms_map["counting-sort"] = {"Counting Sort", CountingSort};
    // algorithms_map["binary-insertion-sort"] = {"Binary Insertion Sort", BinaryInsertionSort};
    // algorithms_map["shaker-sort"] = {"Shaker Sort", ShakerSort}; 
    // algorithms_map["flash-sort"] = {"Flash Sort", FlashSort};
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

// Use to check if an array is sorted or not
bool IsSorted(const int a[], const int n){
    for (int i = 0; i < n - 1; i++){
        if (a[i] > a[i + 1]) return false;
    }
    return true;
}

// Collect data for the report
void CollectDataForReport(){
    // Declare Data Size
    vector<int> data_sizes = {50000};

    // Write the result (running time and number of comparisons) in a result file
    ofstream fout("report_data.txt");
    if (!fout.is_open()) cout << "Cant open result file.\n";

    // for each Data Order S1
    for (pair<string, DataOrderInfo> data_order_info : data_orders_map){
        // Get the data order info
        DataOrderInfo data_order = data_order_info.second;

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
            data_order.function(original_array, size); // data_order.second is the function to generate data

            // for each Sorting Algorithm S3
            for (pair<string, AlgorithmInfo> algorithm_info : algorithms_map){
                // Get the algorithm info
                AlgorithmInfo algorithm = algorithm_info.second;

                // Show the processing message
                cout << "Processing [" << data_order.name << "] with size [" << size << "] using [" << algorithm.name << "]...\n";
                
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
                SortResults result = algorithm.function(duplicated_array, size); // algorithm.second is the function to sort
                
                // Double check if the array is sorted
                if (IsSorted(duplicated_array, size) == false){
                    cout << "The array is not sorted. Ending program...";
                    return;
                }

                // - Take note of S1, S2, S3, running time and number of comparisons
                fout << "[" << data_order.name << "] with size [" << size << "] using [" << algorithm.name << 
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
    /*
    * shellsort sắp xếp trên nửa mảng phía sau
    * sau đó tăng dần ra phía trước
    */
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            // Đặt phần tử vào vị trí đúng
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

void flashSortHelper(int a[], int n)
{
	if (n <= 1) return;

	// Tìm giá trị min và max
	int minVal = a[0], maxVal = 0;
	for (int i = 1; i < n; i++) {
		if (a[i] < minVal) minVal = a[i];
		if (a[i] > maxVal) maxVal = a[i];
	} 

	// nếu min = max thì mảng đã sắp xếp, tất cả các phần tử giống nhau
	if (minVal == maxVal) return;

	// Số lượng bucket
	int m = int(0.43 * n); //chọn 0.43 để tối ưu dựa trên thực nghiệm
	int* bucket = new int[m](); // Mảng đếm cho các bucket, khởi tạo 0

	// Phân loại các phần tử vào bucket
	double c1 = (double)(m - 1) / (maxVal - minVal);
	for (int i = 0; i < n; i++) {
		int k = int(c1 * (a[i] - minVal));
		bucket[k]++;
	}

	// Tính toán chỉ số bắt đầu của mỗi bucket
	for (int i = 1; i < m; i++) {
		bucket[i] += bucket[i - 1];
	}

	// Hoán vị các phần tử vào đúng vị trí
	int i = 0, j = 0;
	while (i < n) {
		int k = int(c1 * (a[i] - minVal));
		if (i >= bucket[k]) {
			i++;
			continue;
		}
		swap(a[i], a[bucket[k] - 1]);
		bucket[k]--;
	}

	// Dùng Insertion Sort để hoàn thành sắp xếp
    // các phần tử đã được phân phối để độ chênh lệch giữa chúngả tốt vì ít phép di chuyển
	InsertionSort(a, bucket[0]);

	delete[] bucket;
}

SortResults FlashSort(int a[], int n)
{
    // Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    // BEGIN SORTING
    flashSortHelper(a, n);
    // END OF SORTING

    // Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Return the result
    return {time, comparisons};
}