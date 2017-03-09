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
const int tests = 15;

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
    void insertionSort(int array[],int size, int testNumber) {
        
        for (int i = 2; i < size; i++) {
            int key = array[i];
            int j = i-1;
            while (j > 0 && array[j] > key) {       //If previous entry is larger, swap it.
                compareCount++;
                array[j+1] = array[j];
                swapCount++;
                j--;
            }
            array[j+1] = key;
            swapCount++;
        }
        arrayCompare[testNumber] = compareCount++;
        arraySwap[testNumber] = swapCount++;
    }
    
//Implementing Merge Sort (Recursive function call found in main)
    void merge(int array[], int size, int low, int mid, int high, int testNumber) {
        int leftIndex = mid - low - 1;
        int rightIndex = high - mid;
        int leftArray[(size/2)+1];          //Hold left half indices plus an end point (hence size / 2)
        for (int i = 0; i < leftIndex+3; i++) {
            leftArray[i] = i+1;
        }
        int rightArray[(size/2)+1];         //Hold right half indices
        for (int i = 0; i < rightIndex+2; i++) {
            rightArray[i] = i+1;
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
        for (int i = 0; i < size1; i++) {       Testing Array Generation
            cout << arrayFwd1[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < size1; i++) {
            cout << arrayRev1[i] << " ";
        }
        */
    }