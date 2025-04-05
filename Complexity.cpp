/*
The term complexity refers to the amount
of resourses required by an algorithm to
solve a problem instance

if an algorithm has time complexity
T(n)=4n^2+100, we simply say the time
complexity is approximated to T(n)≈n^2

Big-oh Notation: O(f(n)) => Worst case
Theta Notation: θ(f(n)) => Average case
Omega Notation: Ω(f(n))=> Best case

functions used in analysis of algorithms:

1. The exponential function
f(n) = 2n

2. The logarithmic function
f(n) = logb n,
The most fundamental
logarithmic function is
g(n) = log2 n

3. The Constant Function
f(n) = c, c is a constant
The most fundamental
constant function is
g(n) = 1
/////////////////////
f(n) is Θ (g(n)) if it is Ω (g(n)) and O(g(n))
*/


#include <iostream>
#include <vector>
#include <algorithm> // For sort function
using namespace std;

// Sorting function with O(n^2) time complexity (Bubble Sort)
void Sort(int x[], int n) {
    // Outer loop runs 'n' times
    for (int i = 0; i < n; i++) {
        // Inner loop runs 'n-i-1' times
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the current element is greater than the next
            if (x[j] > x[j + 1]) {
                swap(x[j], x[j + 1]);
            }
        }
    }
    // Time Complexity:
    // Big-O: O(n^2) => Worst case when the array is in reverse order
    // Theta: θ(n^2) => Average case for random order
    // Omega: Ω(n) => Best case when the array is already sorted
}


// Example: Read, Sort, and Write Algorithm
void Read_sort_write(int n, int m) {
    vector<int> x(n); // Declare an array of size 'n'

    for (int array = 1; array <= m; array++) { // Loop 'm' times
        // Read the array
        cout << "Enter " << n << " elements for array " << array << ": ";
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }

        // Sort the array
        Sort(x.data(), n);

        // Print the sorted array
        cout << "Sorted array " << array << ": ";
        for (int i = 0; i < n; i++) {
            cout << x[i] << " ";
        }
        cout << endl;
    }
    // Time Complexity:
    // T(readArray) = O(n)
    // T(sortArray) = O(n^2)
    // T(printArray) = O(n)
    // T(read + sort + print) = O(n + n^2 + n) = O(n^2)
    // The above three algorithms are executed 'm' times
    // Therefore, the overall time complexity of Read_sort_write is O(m * n^2)
}





// Example 1: O(1) - Constant Time Complexity
// Explanation: The operation takes the same amount of time regardless of the input size.
void constantTimeExample() {
    int x = 42; // Single operation
    cout << "O(1) Example: " << x << endl;
}

// Example 2: O(n) - Linear Time Complexity
// Explanation: The time taken grows linearly with the size of the input.
void linearTimeExample(const vector<int>& arr) {
    cout << "O(n) Example: ";
    for (int num : arr) { // Loop runs 'n' times where 'n' is the size of the array
        cout << num << " ";
    }
    cout << endl;
}

// Example 3: O(n^2) - Quadratic Time Complexity
// Explanation: The time taken grows quadratically with the size of the input.
void quadraticTimeExample(const vector<int>& arr) {
    cout << "O(n^2) Example: " << endl;
    for (size_t i = 0; i < arr.size(); ++i) { // Outer loop runs 'n' times
        for (size_t j = 0; j < arr.size(); ++j) { // Inner loop also runs 'n' times
            cout << arr[i] << ", " << arr[j] << endl; // Total operations = n * n = n^2
        }
    }
}

// Example 4: O(log n) - Logarithmic Time Complexity
// Explanation: The time taken grows logarithmically with the size of the input.
void logarithmicTimeExample(int n) {
    cout << "O(log n) Example: ";
    while (n > 1) { // The loop runs approximately log2(n) times
        cout << n << " ";
        n /= 2; // Halving the input in each iteration
    }
    cout << endl;
}

// Example 5: O(n log n) - Linearithmic Time Complexity
// Explanation: Common in sorting algorithms like Merge Sort or Quick Sort.
void linearithmicTimeExample(vector<int>& arr) {
    cout << "O(n log n) Example: Sorting the array" << endl;
    sort(arr.begin(), arr.end()); // Sorting takes O(n log n) time
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Example 6: O(2^n) - Exponential Time Complexity
// Explanation: The time taken doubles with each additional input size.
int exponentialTimeExample(int n) {
    if (n <= 1) return 1; // Base case
    return exponentialTimeExample(n - 1) + exponentialTimeExample(n - 2); // Recursive calls
}

// Example 7: O(n!) - Factorial Time Complexity
// Explanation: The time taken grows factorially with the size of the input.
void factorialTimeExample(int n, vector<int>& permutation, vector<bool>& used) {
    if (permutation.size() == n) {
        for (int num : permutation) cout << num << " ";
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            used[i] = true;
            permutation.push_back(i);
            factorialTimeExample(n, permutation, used);
            permutation.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    // O(1) Example
    constantTimeExample();

    // O(n) Example
    vector<int> arr = {1, 2, 3, 4, 5};
    linearTimeExample(arr);

    // O(n^2) Example
    quadraticTimeExample(arr);

    // O(log n) Example
    logarithmicTimeExample(16);

    // O(n log n) Example
    linearithmicTimeExample(arr);

    // O(2^n) Example
    cout << "O(2^n) Example: " << exponentialTimeExample(5) << endl;

    // O(n!) Example
    cout << "O(n!) Example: " << endl;
    vector<int> permutation;
    vector<bool> used(6, false); // For n = 5
    factorialTimeExample(5, permutation, used);

    return 0;
}