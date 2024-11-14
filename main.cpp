#include "main.h"

using namespace std;

int main()
{
    //Declare Data Order and Data Size
    vector<int> data_sizes = {10, 30, 50, 100, 300, 500};
    vector<string> data_orders = {"Randomized", "Sorted", "Reverse Sorted", "Nearly Sorted"};
    vector<string> algorithms = {"SelectionSort", "InsertionSort"}; //Finished Algorithm
    //"SelectionSort", "InsertionSort", "HeapSort", "MergeSort", "QuickSort",
    //"RadixSort", "Counting", "BinaryInsertionSort", "ShakerSort", "FlashSort"
    //Add after finish any algorithm
    
    //Write the result (running time and number of comparisons) in a result file
    ofstream fout("sorting_result.txt");
    if (!fout.is_open()) cout << "Cant open result file.\n";

    //Controler Variables
    int data_type = 0; 
    int sort_type = 0;
    // for each Data Order S1
    for (string data_order : data_orders){
        // for each Data Size S2
        for (int size : data_sizes){
            // - Create an original array A1 with Data Order S1 and Data Size S2
            int* original_array = new int[size];
            GenerateData(original_array, size, (data_type)%4);
            // for each Sorting Algorithm S3
            for (string algorithm : algorithms){
                // - Make a duplicate array A2 of the original array A1
                int* duplicated_array = new int[size];
                copy(original_array, original_array + size, duplicated_array);
                // - Sort array A2 using the Sorting Algorithm S3, while:
                    // + Measuring the running time (in millisecs), and
                    // + Counting the number of comparisons in the algorithm

                    //Start measuring running time and counting comparisons
                    auto start = chrono::high_resolution_clock::now();
                    int comparisons = 0;

                    //call sort function
                    SortData(duplicated_array, size, comparisons, (sort_type++)%algorithms.size());

                    //Stop measuring time
                    auto stop = chrono::high_resolution_clock::now();

                    //Calculate running time
                    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                    
                    fout << "[" << data_order << "] with size [" << size << "] using [" << algorithm << "]\t->Time: " << duration.count() << " miliseconds\t\tComparisons: " << comparisons << "\n";
                    //
                // - Take note of S1, S2, S3, running time and number of comparisons
            }
            // end for
        }
        // end for
        data_type++;
    }
    // end for
    fout.close();
}

void SortData(int a[], int n, int &comparisons, int sortType)
{
    switch (sortType)
    {
    case 0:
        SelectionSort(a, n, comparisons);
        break;
    case 1:
        InsertionSort(a, n, comparisons);
        break;
    case 2:
        ShellSort(a, n, comparisons);
        break;
    case 3:
        BubbleSort(a, n, comparisons);
        break;
    case 4:
        HeapSort(a, n, comparisons);
        break;
    case 5:
        MergeSort(a, n, comparisons);
        break;
    case 6:
        QuickSort(a, n, comparisons);
        break;
    case 7:
        RadixSort(a, n, comparisons);
        break;
    case 8:
        CountingSort(a, n, comparisons);
        break;
    case 9:
        BinaryInsertionSort(a, n, comparisons);
        break;
    case 10:
        ShakerSort(a, n, comparisons);
        break;
    case 11:
        FlashSort(a, n, comparisons);
        break;
    default:
        printf("Error: unknown sort type!\n");
    }
}

void SelectionSort(int a[], int n, int &comparisons)
{
    for (int i = 0; i < n; i++){
        int min_index = i;
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[min_index]) min_index = j; comparisons++;
        }
        swap(a[i], a[min_index]);
    }
}

void InsertionSort(int a[], int n, int &comparisons)
{
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
}

void ShellSort(int a[], int n, int &comparions){
    return;
}

void BubbleSort(int a[], int n, int &comparions){
    return;
}

void HeapSort(int a[], int n, int &comparisons)
{
    return;
}

void MergeSort(int a[], int n, int &comparisons)
{
    return;
}

void QuickSort(int a[], int n, int &comparisons)
{
    return;
}

void RadixSort(int a[], int n, int &comparisons)
{
    return;
}

void CountingSort(int a[], int n, int &comparisons)
{
    return;
}

void BinaryInsertionSort(int a[], int n, int &comparisons)
{
    return;
}

void ShakerSort(int a[], int n, int &comparisons)
{
    return;
}

void FlashSort(int a[], int n, int &comparisons)
{
    return;
}