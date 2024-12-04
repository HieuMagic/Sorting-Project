#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "data_generator.cpp"

//struct to store the result
struct SortResults{
    long long time_ms;
    long long comparisons;
};

// Function pointer type for sorting algorithms and data orders
typedef SortResults (*SortFunction)(int*, int);
typedef void (*DataOrderFunction)(int*, int);

// Struct to store the algorithm and data order info
struct AlgorithmInfo{
    string name;
    SortFunction function;
};

struct DataOrderInfo{
    string name;
    DataOrderFunction function;
};

// Support functions
void ListDataOrder();
void ListAlgorithms();
bool IsNumber(const std::string& s);
bool IsSorted(const int a[], const int n);

// Function to collect data for the report
void CollectDataForReport();

// Sorting algorithms functions
SortResults SelectionSort(int *a, int n);
SortResults InsertionSort(int *a, int n);
SortResults ShellSort(int *a, int n);
SortResults BubbleSort(int *a, int n);
SortResults HeapSort(int *a, int n);
SortResults MergeSort(int *a, int n);
SortResults QuickSort(int *a, int n);
SortResults RadixSort(int *a, int n);
SortResults CountingSort(int *a, int n);
SortResults BinaryInsertionSort(int *a, int n);
SortResults ShakerSort(int *a, int n);
SortResults FlashSort(int *a, int n);


