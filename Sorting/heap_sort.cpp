#include <iostream>
#include <algorithm>

using namespace std;

// heap sort
void heapify(int data[], int n, int i)
{
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left child index
    int right = 2 * i + 2; // right child index

    // If left child is larger than root
    if (left < n && data[left] > data[largest])
    {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && data[right] > data[largest])
    {
        largest = right;
    }

    // If largest is not root
    if (largest != i)
    {
        swap(data[i], data[largest]); // Swap root with largest

        // Recursively heapify the affected sub-tree
        heapify(data, n, largest);
    }
}
void heapSort(int data[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(data, n, i);
    }

    // One by one extract elements from heap
    for (int i = n - 1; i >= 0; i--)
    {
        swap(data[0], data[i]); // Move current root to end
        heapify(data, i, 0);    // Call max heapify on the reduced heap
    }
}
/*
Time Complexity:
- Best Case: O(n log n)
- Worst Case: O(n log n)
- Average Case: O(n log n)
Notes:
Heap sort is an in-place sorting algorithm. It builds a max heap from the input data and then repeatedly extracts the maximum element from the heap, rebuilding the heap each time. It is not a stable sorting algorithm.
*/