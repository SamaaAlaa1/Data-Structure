#include <iostream>
#include <algorithm>
using namespace std;

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
            swap(data[i], data[j]); // Swap the current element    with the element at i
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