#include <iostream>
#include <algorithm>

using namespace std;

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
