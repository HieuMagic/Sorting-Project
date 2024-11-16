# Sorting Project

## Welcome
Welcome to the Sorting Project! This project demonstrates various sorting algorithms and their performance.

## How to Use
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the source code using your preferred compiler.
Example with g++:
```bash
g++ -o sorting sorting.cpp
```
4.Your source code can compiled into an executable file (.exe) that can be executed using commands
in the command prompt. The executable file must be placed in the same directory as the source code.

### Here are the commands you can use to run the program:
#### Command 1: Run a sorting algorithm on user-provided data.
    • Prototype: [Execution file] -a [Algorithm] [Input filename]|[Output parameter(s)]
    – Example: a.exe -a radix-sort 70000_random_input.txt -both
#### Command 2: Run a sorting algorithm on the data generated automatically with specified size and order.
    • Prototype: [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]
    – Example: a.exe -a selection-sort 50000 -rand -time
#### Command 3: Run a sorting algorithm on ALL data arrangements of a specified size.
    • Prototype: [Execution file] -a [Algorithm] [Input size] [Output parameter(s)] 
    – Example: a.exe -a counting-sort 70000 -comp
#### Command 4: Run two sorting algorithms on user-provided data.
    • Prototype: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input filename] 
    – Example: a.exe -c heap-sort merge-sort 70000_random_input.txt
#### Command 5: Run two sorting algorithms on the data generated automatically with specified size and order.
    • Prototype: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
    - Example: a.exe -c insertion-sort selection-sort 100000 -nsorted

### Input Arguments: The following arguments are applied for both modes:
#### a. Mode:
    • -a: Algorithm mode
    • -c: Comparison mode
#### b. Algorithm name: Lowercase, words are connected by "-" (Ex: selection-sort, binary- insertion-sort, ...)
    • selection-sort
    • bubble-sort
    • insertion-sort
    • binary-insertion-sort
    • merge-sort
    • quick-sort
    • heap-sort
    • radix-sort
    • shell-sort
    • counting-sort
    • shaker-sort
    • flash-sort
#### c. Input size: Integer (≤ 1,000,000) 
#### d. Input order:
    • -rand: randomized data
    • -nsorted: nearly sorted data 
    • -sorted: sorted data
    • -rev: reverse sorted data
#### e. Given input (file): Path to the input file. The file format is as follows:
    • 1st line: an integer n, indicating the number of elements in the input data 
    • 2nd line: n integers, separated by a single space
#### f. Output parameters
    • -time: algorithms’s running time 
    • -comp: number of comparisions 
    • -both: both above options

