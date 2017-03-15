/* File: SortTest.cpp
 * 
 * Written by: Socratis Katehis
 * 
 * This program tests 3 randomized arrays of different sizes with several sorting algorithms. Part of second report for CSC 22000 algorithms.
 * 
 * Date: 3/2/2017
 * 
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Default values for arrays and program

const int size1 = 100;
const int size2 = 10000;
const int size3 = 1000000;
const int tests = 11;

//Arrays with random integers

int array1[size1];
int array2[size2];
int array3[size3];

//Arrays with integer values 1 to n

int arrayFwd1[size1];
int arrayFwd2[size2];
int arrayFwd3[size3];

//Arrays with integer values n to 1

int arrayRev1[size1];
int arrayRev2[size2];
int arrayRev3[size3];

//Variables storing comparsion and swap count values

int compareCount = 0;
int swapCount = 0;
int arrayCompare[tests];
int arraySwap[tests];

//Function for generating random integer array (Doesn't matter if not-unique)
    void arrayGen(int array[], int size) {
        
        for (int i = 0; i < size; i++) {
            int element = rand() % size;
            array[i] = element;
        }
    }
    
//Function for generating array with integers 1 to n
    void arrayGenFwd(int array[], int size) {
        
        for (int i = 0; i < size; i++) {
            array[i] = i+1;
        }
    }
    
//Function for generating array with integers n to 1
    void arrayGenRev(int array[], int size) {
        
        int lastNumber = size;
        for (int i = 0; i < size; i++) {
            array[i] = lastNumber;
            lastNumber--;
        }
    }
    
//Implementing Straight Insertion Sort
    void insertionSort(int array[],int low, int high, int testNumber) {
        
        for (int i = low; i <= high; i++) {
            int key = array[i];
            int j = i;
            while (j > 1 && array[j-1] > key) {       //If previous entry is larger, swap it.
                compareCount++;
                array[j] = array[j-1];
                swapCount++;
                j--;
            }
            array[j] = key;
            swapCount++;
        }
        
        arrayCompare[testNumber] = compareCount;
        arraySwap[testNumber] = swapCount;
    }
    
//Implementing Merge Sort (Recursive function call found in main)
    void merge(int array[], int low, int mid, int high, int testNumber) {
        
        int leftIndex = mid - low + 1;
        int rightIndex = (high - mid);
        int leftArray[leftIndex];          //Hold left half indices plus an end point (hence size / 2)
        int rightArray[rightIndex];         //Hold right half indices plus an end point
        
        for (int i = 0; i < leftIndex; i++) {
            leftArray[i] = array[low + i];
        }
        for (int i = 0; i < rightIndex; i++) {
            rightArray[i] = array[mid + 1 + i];
        }
        
        int left = 0;
        int right = 0;
        int index = low;
        
        while (left < leftIndex && right < rightIndex) {
            if (leftArray[left] <= rightArray[right]) {
                compareCount++;
                array[index] = leftArray[left++];
                swapCount++;
            }
            else {
                compareCount++;
                array[index] = rightArray[right++];
                swapCount++;
            }
            index++;
        }
        while (left < leftIndex) {             //Copies remaining entries from left array
            compareCount++;
            array[index++] = leftArray[left++];
            swapCount++;
        }
        while (right < rightIndex) {            //Copies remaining entries from right array
            compareCount++;
            array[index++] = rightArray[right++];
            swapCount++;
        }
    }
    
    void mergeSort(int array[], int low, int high, int testNumber) {
        
        if (low < high) {
            int mid = low + (high-low)/2;
            mergeSort(array, low, mid, testNumber);
            mergeSort(array, mid+1, high, testNumber);
            merge(array, low, mid, high, testNumber);
        }
        
        arrayCompare[testNumber] = compareCount;
        arraySwap[testNumber] = swapCount;
        }
        

//TODO: Implement Merge Sort with Straight Insertion Sort when sub-array less than k keys, k is input size when insertionSort better than mergeSort. k = 43 8O(3) < 64O(3log(3))
    
    void insertMergeSort(int array[], int low, int high, int testNumber) {
        
        if (low < high) {
            if ((high-low) < 20) {
                insertionSort(array, low, high, testNumber);
                }
            else {
                int mid = low + (high-low)/2;
                insertMergeSort(array, low, mid, testNumber);
                insertMergeSort(array, mid+1, high, testNumber);
                merge(array, low, mid, high, testNumber);
            }
        }
        arrayCompare[testNumber] = compareCount;
        arraySwap[testNumber] = swapCount;
    }

//Implementing Quick Sort (partitioning function for quick sort)
    int partition(int array[], int low, int high, int testNumber) {
        
        int pivot = array[high];
        int partIndex = low;
        for (int i = low; i < high; i++) {
            if (array[i] <= pivot) {
                compareCount++;
                int temp = array[partIndex];
                array[partIndex] = array[i];
                array[i] =temp;
                swapCount++;
                partIndex++;
            }
        }
        int temp = array[high];
        array[high] = array[partIndex];
        array[partIndex] = temp;
        swapCount++;
        return partIndex;
    }
    
    void quickSort(int array[], int low, int high, int testNumber) {
        if (low < high) {
            int partIndex = partition(array, low, high, testNumber);
            quickSort(array, low, partIndex-1, testNumber);
            quickSort(array, partIndex+1, high, testNumber); 
        }
        arraySwap[testNumber] = swapCount;
        arrayCompare[testNumber] = compareCount;
    }

//TODO: Implement Quick Sort with Straight Insertion Sort when sub-array less than k keys, k is input size when insertionSort better than quickSort.
    void insertQuickSort(int array[], int low, int high, int testNumber) {
        
        if (low < high) {
            if ((high-low) < 50) {
                insertionSort(array, low, high, testNumber);
            }
            else {
                int partIndex = partition(array, low, high, testNumber);
                insertQuickSort(array, low, partIndex-1, testNumber);
                insertQuickSort(array, partIndex+1, high, testNumber); 
            }
        }
        arraySwap[testNumber] = swapCount;
        arrayCompare[testNumber] = compareCount;
    }

//Implementing Heap Sort (build complete binary tree function)
   void buildTree(int array[], int size, int index, int testNumber) {
        
        int largest = index;
        int left = 2*index + 1;
        int right = 2*index + 2;
        
        if (left < size && array[left] > array[largest]) {
            largest = left;
        }
        if (right < size && array[right] > array[largest]) {
            largest = right;
        }
        if (largest != index) {
            compareCount++;
            int temp = array[index];
            array[index] = array[largest];
            array[largest] = temp;
            swapCount++;
            buildTree(array, size, largest, testNumber);
        }
    }
    
    void heapSort(int array[], int size, int testNumber) {
        
        for (int i = size/2 - 1; i >= 0; i--)
            buildTree(array, size, i, testNumber);
        
        for (int i = size-1; i >= 0; i--) {
            int temp = array[0];
            array[0] = array[i];
            array[i] = temp;
            swapCount++;
            buildTree(array, i, 0, testNumber);
        }
        arraySwap[testNumber] = swapCount;
        arrayCompare[testNumber] = compareCount;
    }
    
    void countData(int compareArray[], int swapArray[]) {
        
        int swapSum = 0;
        int comparSum = 0;
        int swapTotal = 0;
        int comparTotal = 0;
        
        for (int i = 0; i < tests; i++) {
            swapSum += swapArray[i];
            comparSum += compareArray[i];
        }
        swapTotal = (swapSum);           
        comparTotal = (comparSum);
        cout << "Swap Average per Test: " << swapTotal;
        cout <<  " Compare Average per Test: " <<  comparTotal << endl;
        
    }
    
     void clearCountData() {
        for (int i = 0; i < tests; i++) {
            arraySwap[i] = 0;
            arrayCompare[i] = 0;
            compareCount = 0;
            swapCount = 0;
        }
    }
    
    int main() {
        
        arrayGenFwd(arrayFwd1, size1);
        arrayGenFwd(arrayFwd2, size2);
        arrayGenFwd(arrayFwd3, size3);
        arrayGenRev(arrayRev1, size1);
        arrayGenRev(arrayRev2, size2);
        arrayGenRev(arrayRev3, size3);
        
        /*
        for (int i = 0; i < size1; i++) {       //Testing Array Generation
            cout << arrayFwd1[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < size1; i++) {
            cout << arrayRev1[i] << " ";
        }
        cout << endl;
        */
        cout << " \n Sorting First Forward Array with Insertion Sort. \n" << endl;
        insertionSort(arrayFwd1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " Sorting First Array with Insertion Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array1, size1);
            insertionSort(array1, 0, size1-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting First Reverse Array with Insertion Sort. \n" << endl;
        insertionSort(arrayRev1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting First Forward Array with Merge Sort. \n" << endl;
        mergeSort(arrayFwd1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting First Array with Merge Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array1, size1);
            mergeSort(array1, 0, size1-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting First Reverse Array with Merge Sort. \n" << endl;
        mergeSort(arrayRev1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting First Forward Array with Insertion Merge Sort. \n" << endl;
        insertMergeSort(arrayFwd1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting First Array with Insertion Merge Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array1, size1);
            insertMergeSort(array1, 0, size1-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting First Reverse Array with Insertion Merge Sort. \n" << endl;
        insertMergeSort(arrayRev1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting First Forward Array with Quick Sort. \n" << endl;
        quickSort(arrayFwd1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting First Array with Quick Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array1, size1);
            quickSort(array1, 0, size1-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting First Reverse Array with Quick Sort. \n" << endl;
        quickSort(arrayRev1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting First Forward Array with Insertion Quick Sort. \n" << endl;
        insertQuickSort(arrayFwd1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting First Array with Insertion Quick Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array1, size1);
            insertQuickSort(array1, 0, size1-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting First Reverse Array with Insertion Quick Sort. \n" << endl;
        insertQuickSort(arrayRev1, 0, size1-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting First Forward Array with Heap Sort. \n" << endl;
        heapSort(arrayFwd1, size1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting First Array with Heap Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array1, size1);
            heapSort(array1, size1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting First Reverse Array with Heap Sort. \n" << endl;
        heapSort(arrayRev1, size1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Second Forward Array with Insertion Sort. \n" << endl;
        insertionSort(arrayFwd2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Second Array with Insertion Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array2, size2);
            insertionSort(array2, 0, size2-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Second Reverse Array with Insertion Sort. \n" << endl;
        insertionSort(arrayRev2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Second Forward Array with Merge Sort. \n" << endl;
        mergeSort(arrayFwd2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Second Array with Merge Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array2, size2);
            mergeSort(array2, 0, size2-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Second Reverse Array with Merge Sort. \n" << endl;
        mergeSort(arrayRev2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Second Forward Array with Insertion Merge Sort. \n" << endl;
        insertMergeSort(arrayFwd2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Second Array with Insertion Merge Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array2, size2);
            insertMergeSort(array2, 0, size2-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Second Reverse Array with Insertion Merge Sort. \n" << endl;
        insertMergeSort(arrayRev2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Second Forward Array with Quick Sort. \n" << endl;
        quickSort(arrayFwd2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Second Array with Quick Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array2, size2);
            quickSort(array2, 0, size2-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Second Reverse Array with Quick Sort. \n" << endl;
        quickSort(arrayRev2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Second Forward Array with Insertion Quick Sort. \n" << endl;
        insertQuickSort(arrayFwd2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Second Array with Insertion Quick Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array2, size2);
            insertQuickSort(array2, 0, size2-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Second Forward Array with Insertion Quick Sort. \n" << endl;
        insertQuickSort(arrayFwd2, 0, size2-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Second Forward Array with Heap Sort. \n" << endl;
        heapSort(arrayFwd2, size2, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Second Array with Heap Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array2, size2);
            heapSort(array2, size2, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Second Reverse Array with Heap Sort. \n" << endl;
        insertionSort(arrayFwd2,0, size2, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Third Forward Array with Insertion Sort. \n" << endl;
        insertionSort(arrayFwd3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Third Array with Insertion Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array3, size3);
            insertionSort(array3, 0, size3-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Third Reverse Array with Insertion Sort. \n" << endl;
        insertionSort(arrayRev3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Third Forward Array with Merge Sort. \n" << endl;
        mergeSort(arrayFwd3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Third Array with Merge Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array3, size3);
            mergeSort(array3, 0, size3-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Third Reverse Array with Merge Sort. \n" << endl;
        mergeSort(arrayRev3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Third Forward Array with Insertion Merge Sort. \n" << endl;
        insertMergeSort(arrayFwd3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Third Array with Insertion Merge Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array3, size3);
            insertMergeSort(array3, 0, size3-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Third Reverse Array with Insertion Merge Sort. \n" << endl;
        insertMergeSort(arrayRev3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Third Forward Array with Quick Sort. \n" << endl;
        quickSort(arrayFwd3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Third Array with Quick Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array3, size3);
            quickSort(array3, 0, size3-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Third Reverse Array with Quick Sort. \n" << endl;
        quickSort(arrayRev3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Third Forward Array with Insertion Quick Sort. \n" << endl;
        insertQuickSort(arrayFwd3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Third Array with Insertion Quick Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array3, size3);
            insertQuickSort(array3, 0, size3-1, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Third Reverse Array with Insertion Quick Sort. \n" << endl;
        insertQuickSort(arrayRev3, 0, size3-1, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << " \n Sorting Third Forward Array with Heap Sort. \n" << endl;
        heapSort(arrayFwd3, size3, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
        cout << "\n Sorting Third Array with Heap Sort. \n" << endl;
        for (int i = 0; i < tests; i++) {
            arrayGen(array3, size3);
            heapSort(array3, size3, i);
            countData(arrayCompare, arraySwap);
            clearCountData();
        }
        
        cout << " \n Sorting Third Forward Array with Heap Sort. \n" << endl;
        heapSort(arrayRev3, size3, 1);
        countData(arrayCompare, arraySwap);
        clearCountData();
        
    }