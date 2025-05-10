/*
Two factors determine the algorithm
performance:
The number of comparisons
The number of movements
*/
#include <iostream>
#include <algorithm>

using namespace std;

// insertion sort
void insertionSort(int data[], int n) {
    // Traverse from the second element to the last
    for (int i = 1; i < n; i++) {
        int key = data[i]; // Store the current element
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }

        // Place the key in its correct position
        data[j + 1] = key;
    }
}

/*
Time Complexity:
- Best Case (Already Sorted): O(n)
- Worst Case (Reverse Sorted): O(n^2)
- Average Case: O(n^2)

Notes:
The number of shifts performed during an insertion is
one less than the number of comparisons or, when the
new value is the smallest so far, the same as the number
of comparisons.
*/

///////////////////////////////////////////////////////////////////////////
// selection sort

void selectionSort(int data[], int n) {
    // Traverse through all array elements
    for (int i = 0; i < n - 1; i++) {
        // Find the minimum element in the unsorted part
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element
        if (minIndex != i) {
            swap(data[i], data[minIndex]);
        }
    }
}


/*
Time Complexity:
- Best Case: O(n^2)
- Worst Case: O(n^2)
- Average Case: O(n^2)

Notes:
Selection sort performs the same number of comparisons
in every case, regardless of the initial order of the elements.
The Selection Sort might swap an array
element with itself--this is harmless,
and not worth checking for
*/
///////////////////////////////////////////////////////////////////////////
// bubble sort

void bubbleSort(int data[], int n) {
    // Traverse through all array elements
    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already sorted
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the element found is greater than the next element
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

/*
Time Complexity:
- Best Case (Already Sorted):O(n^2) can be improved to O(n)
In the best case, the array is already sorted, so no swaps are needed.
To optimize for this case, we can introduce a flag to check if any swaps
occurred during a pass. If no swaps are made, the algorithm can terminate early.

- Worst Case (Reverse Sorted): O(n^2)
- Average Case: O(n^2)

Notes:
Bubble sort is a stable sorting algorithm. It repeatedly
steps through the list, compares adjacent elements, and
swaps them if they are in the wrong order.
Provides excellent performance in some cases and very
poor performances in other cases
Main problem: it moves data up, one step at a time
*/

void optimizedBubbleSort(int data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // Flag to check if any swaps occurred
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                swapped = true;
            }
        }
        // If no swaps occurred, the array is already sorted
        if (!swapped) {
            break;
        }
    }
}
/////////////////////////////////////////////////////////////////////////
/*Comparison of Quadratic Sorts
Bubble Sort, Selection Sort, and Insertion Sort are all O(n2)
As we will see later, we can do much better than this with
somewhat more complicated sorting algorithms Within O(n^2),

-Bubble Sort is very slow, and should probably never be used for anything

-Selection Sort is intermediate in speed

-Insertion Sort is usually the fastest of the three--in fact, for
small arrays (say, 10 or 15 elements), insertion sort is
faster than more complicated sorting algorithms

-Selection Sort and Insertion Sort are “good enough” for small
arrays

*/