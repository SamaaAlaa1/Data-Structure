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
somewhat more complicated sorting algorithms Within O(n2),

-Bubble Sort is very slow, and should probably never be
used for anything

-Selection Sort is intermediate in speed

-Insertion Sort is usually the fastest of the three--in fact, for
small arrays (say, 10 or 15 elements), insertion sort is
faster than more complicated sorting algorithms

-Selection Sort and Insertion Sort are “good enough” for small
arrays

*/
///////////////////////////////////////////////////////////////////
// shell sort
/*Shell sort is a type of insertion sort but with O(n^(3/2)) or better performance*/
void shellSort(int data[], int n) {
    // Start with a large gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            int temp = data[i];
            int j;
            // Shift earlier gap-sorted elements up until the correct location for data[i] is found
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                data[j] = data[j - gap];
            }
            // Put temp (the original data[i]) in its correct location
            data[j] = temp;
        }
    }
}

/*
Time Complexity:
- Best Case: O(n log n)
- Worst Case: O(n^2)
- Average Case: Depends on the gap sequence, but generally better than O(n^2) ,O(n^(3/2)) 

Notes:
Shell sort is an optimization over insertion sort. It allows the exchange of far-apart elements,
which can move elements closer to their correct positions faster. The choice of gap sequence
significantly affects the performance of the algorithm.
*/
/////////////////////////////////////////////////////////////////
// merge sort
void merge(int data[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int leftArray[n1];
    int rightArray[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArray[i] = data[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = data[mid + 1 + j];

    // Merge the temporary arrays back into data[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            data[k] = leftArray[i];
            i++;
        } else {
            data[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray, if any
    while (i < n1) {
        data[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray, if any
    while (j < n2) {
        data[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int data[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);

        // Merge the sorted halves
        merge(data, left, mid, right);
    }
}

/*
Time Complexity:
- Best Case: O(n log n)
- Worst Case: O(n log n)
- Average Case: O(n log n)

Notes:
Merge sort is a stable sorting algorithm. It divides the array into halves,
sorts them recursively, and then merges the sorted halves. It is not an
in-place sorting algorithm as it requires additional memory for merging.

-needs more space than other sorts.

Base Case:
The base case for merge sort occurs when the array to be sorted has only one element.
In this case, the array is already sorted, and no further action is needed.
This is represented by the condition `if (left < right)` in the `mergeSort` function.
When `left` is not less than `right`, the recursion stops.
*/
/////////////////////////////////////////////////////////////////
// quick sort
int partition(int data[], int left, int right) {
    int pivot = data[left]; // Choose the first element as the pivot
    int i = left; // Index for elements smaller than the pivot

    for (int j = left + 1; j <= right; j++) {
        if (data[j] < pivot) {
            i++; // Move the index for smaller elements
            swap(data[i], data[j]); // Swap the current element with the element at i
        }
    }
    // Swap the pivot element into its correct position
    swap(data[i], data[left]); 
    return i; // Return the partition index
}

void quickSort(int data[], int left, int right) {
    if (left < right) {
        int pi = partition(data, left, right); // Partitioning index

        quickSort(data, left, pi - 1);  // Sort the left part
        quickSort(data, pi + 1, right); // Sort the right part
    }
}


/*
Time Complexity:
- Best Case (Pivot divides the array into two equal halves): O(n log n)
- Worst Case (Pivot is the smallest or largest element): O(n^2)
- Average Case: O(n log n)

Notes:
Quick sort is an in-place sorting algorithm and is generally faster than merge sort
for large datasets. However, its performance depends on the choice of the pivot.
To improve performance, techniques like random pivot selection or the median-of-three
method can be used.
*/
/////////////////////////////////////////////////////////////////
// count sort
void countSort(int data[], int n) {
    // Find the maximum element in the array
    int maxElement = *max_element(data, data + n);

    // Create a count array to store the frequency of each element
    int count[maxElement + 1] = {0};

    // Store the count of each element
    for (int i = 0; i < n; i++) {
        count[data[i]]++;
    }

    // Modify the count array such that each element at each index
    // stores the sum of previous counts (cumulative count)
    for (int i = 1; i <= maxElement; i++) {
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted elements
    int output[n];

    // Build the output array by placing elements in their correct position
    for (int i = n - 1; i >= 0; i--) {
        output[count[data[i]] - 1] = data[i];
        count[data[i]]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++) {
        data[i] = output[i];
    }
}

/*
Time Complexity:
- Best Case: O(n + k)
- Worst Case: O(n + k)
- Average Case: O(n + k)

Where n is the number of elements in the array and k is the range of the input.

Notes:
Count sort is not a comparison-based sorting algorithm. It is efficient for sorting
integers or objects that can be mapped to integers within a limited range. However,
it is not suitable for sorting large datasets with a wide range of values due to
its space complexity.
stable sort

Counting sort array size limitation problem:

-If we need sort 32 bits integers, size of count array 2^32 = 4GB !

-Unsorted array size is usually smaller than this (1KB << 4GB)

-Solution... Use smaller parts like digits and sort these parts particularly : Radix sort
*/
/////////////////////////////////////////////////////////////////
// radix sort
int getMax(int data[], int n) {
    int maxElement = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] > maxElement) {
            maxElement = data[i];
        }
    }
    return maxElement;
}

void countingSortForRadix(int data[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    // Count occurrences of digits
    for (int i = 0; i < n; i++) {
        count[(data[i] / exp) % 10]++;
    }

    // Update count array to store cumulative counts
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(data[i] / exp) % 10] - 1] = data[i];
        count[(data[i] / exp) % 10]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++) {
        data[i] = output[i];
    }
}

void radixSort(int data[], int n) {
    int maxElement = getMax(data, n);

    // Perform counting sort for each digit
    for (int exp = 1; maxElement / exp > 0; exp *= 10) {
        countingSortForRadix(data, n, exp);
    }
}

/*
Time Complexity:
- Best Case: O(nk)
- Worst Case: O(nk)
- Average Case: O(nk)

Where n is the number of elements in the array and k is the number of digits in the largest number.

Notes:
Radix sort is a non-comparative sorting algorithm. It processes the digits of numbers
starting from the least significant digit to the most significant digit. It is efficient
for sorting integers or strings with a fixed length.
*/
//////////////////////////////////////////////////////////
// bucket sort
void bucketSort(float data[], int n) {
    // Create n empty buckets
    float buckets[n][n]; // 2D array for buckets
    int bucketSizes[n] = {0}; // Array to track the size of each bucket

    // Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * data[i]; // Index in bucket
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = data[i];
    }

    // Sort individual buckets
    for (int i = 0; i < n; i++) {
        sort(buckets[i], buckets[i] + bucketSizes[i]);
    }

    // Concatenate all buckets into data[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            data[index++] = buckets[i][j];
        }
    }
}

/*
Time Complexity:
- Best Case: O(n + k)
- Worst Case: O(n^2) (when all elements are in one bucket)
- Average Case: O(n + k)

Where n is the number of elements and k is the number of buckets.

Notes:
- The performance of bucket sort depends on the distribution of the input data and the number of buckets.
- It is not a comparison-based sorting algorithm and works well for floating-point numbers or integers within a specific range.
- The choice of the number of buckets and the method used to sort individual buckets can significantly affect its efficiency.
- Bucket sort is not suitable for datasets with a large range of values or non-uniform distributions.
*/
int main(){

    return 0;
}