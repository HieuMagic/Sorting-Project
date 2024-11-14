#include "main.h"

using namespace std;

// Function pointer type for sorting algorithms
typedef SortResults (*SortFunction)(int*, int);
typedef void (*DataOrder)(int*, int);

//Map to store the algorithm names and names of the function to call them
map<string, SortFunction> sorting_algorithms;
map<string, DataOrder> data_orders;

int main(int argc, char* argv[])
{
    //Add all the finished algorithms to the map
    ListAlgorithms();
    ListDataOrder();

    //We will collect data for report if there isn't any argument
    if (argc == 1){
        CollectDataForReport();
        return 0;
    }
}

struct SortResults{
    double time_ms;
    long long comparisons;
};

void ListDataOrder(){
    //ADD DATA ORDER HERE
    data_orders["randomized"] = GenerateRandomData;
    data_orders["sorted"] = GenerateSortedData;
    data_orders["reverse"] = GenerateReverseData;
    data_orders["nearly_sorted"] = GenerateNearlySortedData;
    //
}

void ListAlgorithms(){
    //ADD ALGORITHMS HEHE
    sorting_algorithms["selection-sort"] = SelectionSort;
    sorting_algorithms["insertion-sort"] = InsertionSort;
    // Only add algorithms that are fully implemented
    //"SelectionSort", "InsertionSort", "HeapSort", "MergeSort", "QuickSort",
    //"RadixSort", "Counting", "BinaryInsertionSort", "ShakerSort", "FlashSort"
}

void CollectDataForReport(){
    //Declare Data Size
    vector<int> data_sizes = {10, 30, 50, 100, 300, 500};

    //Write the result (running time and number of comparisons) in a result file
    ofstream fout("sorting_result.txt");
    if (!fout.is_open()) cout << "Cant open result file.\n";

    // for each Data Order S1
    for (pair<string, DataOrder> data_order : data_orders){
        // for each Data Size S2
        for (int size : data_sizes){
            // - Create an original array A1 with Data Order S1 and Data Size S2
            int* original_array = new int[size];
            data_order.second(original_array, size);
            // for each Sorting Algorithm S3
            for (pair<string, SortFunction> algorithm : sorting_algorithms){
                // - Make a duplicate array A2 of the original array A1
                int* duplicated_array = new int[size];
                copy(original_array, original_array + size, duplicated_array);
                // - Sort array A2 using the Sorting Algorithm S3, while:
                    // + Measuring the running time (in millisecs), and
                    // + Counting the number of comparisons in the algorithm
                SortResults result = algorithm.second(duplicated_array, size);
                
                // - Take note of S1, S2, S3, running time and number of comparisons
                fout << "[" << data_order.first << "] with size [" << size << "] using [" << algorithm.first << 
                        "]\t->Time: " << result.time_ms << " miliseconds\t\tComparisons: " << result.comparisons << "\n";
            }
            // end for
        }
        // end for
    }
    // end for
    fout.close();
}

SortResults SelectionSort(int a[], int n)
{
    //Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    //BEGIN SORTING
    for (int i = 0; i < n; i++){
        int min_index = i;
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[min_index]) min_index = j; comparisons++;
        }
        swap(a[i], a[min_index]);
    }
    //END OF SORTING

    //Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    double time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    //Return the result
    return {time, comparisons};
}

SortResults InsertionSort(int a[], int n)
{
    //Start counting time and comparisons
    long long comparisons = 0;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    
    //BEGIN SORTING
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
    //END OF SORTING

    //Stop counting and calculate time 
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    double time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    //Return the result
    return {time, comparisons};
}

SortResults ShellSort(int a[], int n)
{
    return {0,0};
}

SortResults BubbleSort(int a[], int n)
{
    return {0,0};
}

SortResults HeapSort(int a[], int n)
{
    return {0,0};
}

SortResults MergeSort(int a[], int n)
{
    return {0,0};
}

SortResults QuickSort(int a[], int n)
{
    return {0,0};
}

SortResults RadixSort(int a[], int n)
{
    return {0,0};
}

SortResults CountingSort(int a[], int n)
{
    return {0,0};
}

SortResults BinaryInsertionSort(int a[], int n)
{
    return {0,0};
}

SortResults ShakerSort(int a[], int n)
{
    return {0,0};
}

SortResults FlashSort(int a[], int n)
{
    return {0,0};
}