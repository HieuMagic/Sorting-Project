#include "sorting.cpp"

using namespace std;

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
        // Get the algorithm command
        string algorithm_command= argv[2];

        // Check if the algorithm command is valid or not
        if (algorithms_map.count(algorithm_command) == 0){
            cout << "The algorithm isn't exist in the algorithms list. Ending program...";
            return 1;
        }

        // Get the algorithm name and function pointer
        AlgorithmInfo algorithm = algorithms_map[algorithm_command];

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
                int* original_array = new int[size];
                for (int i = 0; i < size; i++){
                    original_array[i] = stoi(data_line.substr(data_index, data_line.find(' ', data_index) - data_index));
                    data_index = data_line.find(' ', data_index) + 1;
                }
                
                // Duplicate the array
                int* duplicated_array = new int[size];
                copy(original_array, original_array + size, duplicated_array);

                // Sort the array and get the result
                SortResults result = algorithm.function(duplicated_array, size);
                
                // Write the sorted array to the output file
                ofstream fout("output.txt");
                if (!fout.is_open()){
                    cout << "Unable to open output file. Ending program...";
                    return 1;
                }
                for (int i = 0; i < size; i++){
                    fout << duplicated_array[i] << " ";
                }

                // Check if we need to show time or number of comparions or both
                bool show_time = false;
                bool show_comparisons = false;
                if (output_parameter == "-time" || output_parameter == "-both") show_time = true;
                if (output_parameter == "-comp" || output_parameter == "-both") show_comparisons = true;

                // Show the results
                cout << "ALGORITHM MODE\n";
                cout << "Algorithm: " << algorithm.name << "\n";
                cout << "Input file: " << filename << '\n';
                cout << "input size: " << size << "\n";
                cout << "----------------------------------\n";
                if (show_time) cout << "Running time: " << result.time_ms << "\n";
                if (show_comparisons) cout << "Comparison: " << result.comparisons << "\n";

                delete[] original_array;
                delete[] duplicated_array;
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
                cout << "Algorithm: " << algorithm.name << "\n";
                cout << "Input size: " << size << '\n';
                
                // Initialize the input file index
                string input_file_index = "1";

                // For each data order, we print the results
                for (pair<string, DataOrderInfo> data_order_info : data_orders_map)
                {
                    // Get the data order info
                    DataOrderInfo data_order = data_order_info.second;

                    // Create the array based on the data_order and size
                    int* original_array = new int[size];
                    data_order.function(original_array, size);

                    // Duplicate the array
                    int* duplicated_array = new int[size];
                    copy(original_array, original_array + size, duplicated_array);

                    // Sort the array and get the result
                    SortResults result = algorithm.function(duplicated_array, size);
                    
                    // Write the generated array to the input file 
                    // (This run 4 times and each time we write to input_1.txt, input_2.txt, input_3.txt, input_4.txt)
                    ofstream fout("input_" + input_file_index + ".txt");
                    if (!fout.is_open()){
                        cout << "Unable to open output file. Ending program...";
                        return 1;
                    }

                    for (int i = 0; i < size; i++){
                        fout << original_array[i] << " ";
                    }

                    // Increase the input file index
                    input_file_index[0]++;

                    // Check if we need to show time or number of comparions or both
                    bool show_time = false;
                    bool show_comparisons = false;
                    if (output_parameter == "-time" || output_parameter == "-both") show_time = true;
                    if (output_parameter == "-comp" || output_parameter == "-both") show_comparisons = true;

                    cout << "Input order: " << data_order.name << "\n";
                    cout << "----------------------------------\n";
                    if (show_time) cout << "Running time: " << result.time_ms << "\n";
                    if (show_comparisons) cout << "Comparison: " << result.comparisons << "\n";
                    cout << "\n";
                    
                    delete[] original_array;
                    delete[] duplicated_array;
                    fout.close();
                }
            }
        }
        // COMMAND 2
        else if (argc == 6){ // Which is the command 2's number of arguments. We run command 2
            // Get data from argurment
            int size = stoi(argv[3]);
            string output_parameter = argv[5];
            string data_order_command = argv[4];

            // Check if command is valid or not
            if (data_orders_map.count(data_order_command) == 0){
                cout << "The data order isn't exist in the data_orders_map list. Ending program...";
                return 1;
            }

            // Get the data order info
            DataOrderInfo data_order = data_orders_map[data_order_command];

            // Create array
            int* original_array = new int[size];
            data_order.function(original_array, size);

            // duplicate the array
            int* duplicated_array = new int[size];
            copy(original_array, original_array + size, duplicated_array);

            // Sort the array and get the result
            SortResults result = algorithm.function(duplicated_array, size);
            
            // Write the generated array to the input file
            ofstream fout("input.txt");
            if (!fout.is_open()){
                cout << "Unable to open output file. Ending program...";
                return 1;
            }

            for (int i = 0; i < size; i++){
                fout << original_array[i] << " ";
            }

            // Write the sorted array to the output file
            ofstream fout2("output.txt");
            if (!fout2.is_open()){
                cout << "Unable to open output file. Ending program...";
                return 1;
            }

            for (int i = 0; i < size; i++){
                fout2 << duplicated_array[i] << " ";
            }

            // Check if we need to show time or number of comparions or both
            bool show_time = false;
            bool show_comparisons = false;
            if (output_parameter == "-time" || output_parameter == "-both") show_time = true;
            if (output_parameter == "-comp" || output_parameter == "-both") show_comparisons = true;

            // Show the results
            cout << "ALGORITHM MODE\n";
            cout << "Algorithm: " << algorithm.name << "\n";
            cout << "Input size: " << size << '\n';
            cout << "input order: " << data_order.name << "\n";
            cout << "----------------------------------\n";
            if (show_time) cout << "Running time: " << result.time_ms << "\n";
            if (show_comparisons) cout << "Comparison: " << result.comparisons << "\n";

            delete[] original_array;
            delete[] duplicated_array;
            fout.close();
            fout2.close();
        }
        else {
            cout << "Too many/few arguments. Ending program...";
            return 1;
        }
    }
    else if (flag == "-c"){
        // Get the algorithm commands
        string algorithm_1_command = argv[2];
        string algorithm_2_command = argv[3];

        // Check if the algorithm commands are valid or not
        if (algorithms_map.count(algorithm_1_command) == 0 || algorithms_map.count(algorithm_2_command) == 0){
            cout << "The algorithm isn't exist in the algorithms list. Ending program...";
            return 1;
        }

        // Get the algorithm info
        AlgorithmInfo algorithm_1 = algorithms_map[algorithm_1_command];
        AlgorithmInfo algorithm_2 = algorithms_map[algorithm_2_command];

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
            int* original_array = new int[size];
            for (int i = 0; i < size; i++){
                original_array[i] = stoi(data_line.substr(data_index, data_line.find(' ', data_index) - data_index));
                data_index = data_line.find(' ', data_index) + 1;
            }

            // Duplicate the array
            int* duplicated_array = new int[size];
            copy(original_array, original_array + size, duplicated_array);
            // Sort the array and get the results
            SortResults result_1 = algorithm_1.function(duplicated_array, size);

            // Duplicate the array again
            copy(original_array, original_array + size, duplicated_array);
            // Sort the array and get the results
            SortResults result_2 = algorithm_2.function(duplicated_array, size);

            // Show the results
            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algorithm_1.name << " | " << algorithm_2.name <<  "\n";
            cout << "Input file: " << filename << '\n';
            cout << "Input size: " << size << "\n";
            cout << "----------------------------------\n";
            cout << "Running time: " << result_1.time_ms << " | " << result_2.time_ms << "\n";
            cout << "Comparison: " << result_1.comparisons << " | " << result_2.comparisons << "\n";

            delete[] original_array;
            delete[] duplicated_array;
            fin.close();
        }
        // COMMAND 5
        else if (argc == 6){ // Which is the command 5's number of arguments. We run command 5
            // Get data from argurment
            int size = stoi(argv[4]);
            string data_order_command = argv[5];

            // Check if command is valid or not
            if (data_orders_map.count(data_order_command) == 0){
                cout << "The data order isn't exist in the data_orders_map list. Ending program...";
                return 1;
            }

            // Get the data order info
            DataOrderInfo data_order = data_orders_map[data_order_command];

            // Create array
            int* original_array = new int[size];
            int* duplicated_array = new int[size];
            // Generate the array based on the input order
            data_order.function(original_array, size);

            // Duplicate the array
            copy(original_array, original_array + size, duplicated_array);
            // Sort the array and get the results
            SortResults result_1 = algorithm_1.function(duplicated_array, size);

            // Duplicate the array again
            copy(original_array, original_array + size, duplicated_array);
            // Sort the array and get the results
            SortResults result_2 = algorithm_2.function(duplicated_array, size);

            // Write the generated array to the input file
            ofstream fout("input.txt");
            if (!fout.is_open()){
                cout << "Unable to open output file. Ending program...";
                return 1;
            }

            for (int i = 0; i < size; i++){
                fout << original_array[i] << " ";
            }

            // Show the results
            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algorithm_1.name << " | " << algorithm_2.name <<  "\n";
            cout << "Input size: " << size << "\n";
            cout << "Input order: " << data_order.name << "\n";
            cout << "----------------------------------\n";
            cout << "Running time: " << result_1.time_ms << " | " << result_2.time_ms << "\n";
            cout << "Comparison: " << result_1.comparisons << " | " << result_2.comparisons << "\n";

            delete[] original_array;
            delete[] duplicated_array;
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
