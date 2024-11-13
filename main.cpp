#include <vector>
#include "data_generator.cpp"

using namespace std; 

int main()
{
    //Declare Data Order and Data Size
    vector<int> n = {10000, 30000, 50000, 100000, 300000, 500000};
    vector<int*> sorted, nearly_sorted, reverse_sorted, randomized;

    //Generate data for each Data Order. 
    //Size of each array based on index [0]: 10000, [1]: 30000, [2]50000, [3]100000, [4]300000, [5]500000.
    for(int i = 0; i < n.size(); i++){
        //Initialize each data order with size n[i]
        int* sorted_array = new int[n[i]];
        int* nearly_sorted_array = new int[n[i]];
        int* reverse_sorted_array = new int[n[i]];
        int* randomized_array = new int[n[i]];

        //Generate data
        GenerateSortedData(sorted_array, n[i]);
        GenerateNearlySortedData(nearly_sorted_array, n[i]);
        GenerateReverseData(nearly_sorted_array, n[i]);
        GenerateRandomData(randomized_array, n[i]);

        //Add array to holder and move on
        sorted.push_back(sorted_array);
        nearly_sorted.push_back(nearly_sorted_array);
        reverse_sorted.push_back(reverse_sorted_array);
        randomized.push_back(randomized_array);
    }

    //Check if data is successfully generated
    //cout << randomized[5][499999];

}