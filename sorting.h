#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include "data_generator.cpp"

//struct to store the result
struct SortResults{
    long long time_ms;
    long long comparisons;
};

//
void ListDataOrder();
void ListAlgorithms();
void CollectDataForReport();
bool is_number(const std::string& s);
bool IsSorted(const int a[], const int n);

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


