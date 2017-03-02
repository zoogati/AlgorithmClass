/* File: SearchTest.cpp
 * 
 * Written by: Socratis Katehis
 * 
 * This program tests 4 uniquely randomized arrays of different sizes with several sorting and searching algorithms. Part of first report for CSC 22000 algorithms.
 * 
 * Date: 2/9/2017
 * 
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
// Default values for our program.

   const int size1 = 100;
   const int size2 = 10000;
   const int size3 = 100000;
   const int size4 = 100000000;
   const int sizeKey = 1000;
   const int tests = 100;
    
    int array1[size1];
    int array2[size2];
    int array3[size3];
    int array4[size4];
    int arrayKey[sizeKey];
    
    int arrayLoop[sizeKey];
    int arrayCompare[sizeKey];
    
    int countFound = 0;
    int falseOperation = 0;
    
    // Function for generating uniquely randomized arrays
    void arrayGen(int array[],int size) {

        for(int i = 0; i<size; i++)                         // 3*n + 2
        {
            int element = rand() % (6*size);                //WARNI
            array[i] = element;
            for (int j = 0; j<i; j++) {
                if (array[i] == array[j]) {
                    i--;
                    break;
                }
            }
        }
       /* for (int k = 0; k<size; k++) {
            cout << array[k] << endl;
        } */
        //cout << "End of array \n" << endl;
    }
    
    //Function for generating randomized array (used for keys)
    void arrayKeyGen(int array[], int size) {
        
        for (int i = 0; i<size; i++) {
            int element = rand() % size;
            array[i] = element;
        }
    }
    
    //Implementing Sequential Search
    bool sequentialSearch(int array[], int size, int key, int testNumber) {
        
        int loopCount = 0;
        int comparisonCount = 0;
        int trueOperation = 0;
        int falseOperation = 0;
        
        for (int i = 0; i < size; i++) {
            loopCount++;                                    // 3*n + 2
            if (array[i] == key) {                          // n
                comparisonCount++;                          // n
                arrayLoop[testNumber] = loopCount;          // n
                arrayCompare[testNumber] = comparisonCount; // n
                countFound++;                               // n
                return true;
            }
        }
            comparisonCount++;                              // n
            arrayLoop[testNumber] = loopCount;              // n
            arrayCompare[testNumber] = comparisonCount;     // n
            return false;
    }
    
    //Implementing Indexed Sequential Search
    bool indexSequentialSearch(int array[], int size, int key, int testNumber) {
        
        int loopCount = 0;
        int comparisonCount = 0;
        
        int newIndex = log10(size);     //Indexing step is power of size.
         for (int i = 0; i < size; i += newIndex) {
            loopCount++;                                    // 3*n +2
            if (array[i] == key) {                          // n
                comparisonCount++;                          // n
                arrayLoop[testNumber] = loopCount;          // n
                arrayCompare[testNumber] = comparisonCount; // n
                countFound++;                               // n
                return true;
            }
        }
            comparisonCount++;                              // n
            arrayLoop[testNumber] = loopCount;              // n
            arrayCompare[testNumber] = comparisonCount;     // n
            return false;
    }
    
    //Implementing Sequential Search with first element swap
    bool sequentialSearchFirst(int array[], int size, int key, int testNumber) {
       
        int loopCount = 0;
        int comparisonCount = 0;
        
        for (int i = 0; i < size; i++) {
            loopCount++;
            if (array[i] == key) {
                comparisonCount++;
                int temp = array[i];
                array[i] = array[0];
                array[0] = temp;
                arrayLoop[testNumber] = loopCount;
                arrayCompare[testNumber] = comparisonCount;
                return true;
            }
        }
            arrayLoop[testNumber] = loopCount;
            arrayCompare[testNumber] = comparisonCount;
            return false;
    }
            
    //Implementing Sequential Search with next element swap
    bool sequentialSearchNext(int array[], int size, int key, int testNumber) {
        
        int loopCount = 0;
        int comparisonCount =0;
        
         for (int i = 0; i < size; i++) {
            loopCount++;
            if (array[i] == key) {
                comparisonCount++;
                int temp = array[i];
                array[i] = array[i-1];
                array[i-1] = temp;
                cout << "Found it :) \n" <<  endl;
                // countData(loopCount, comparisonCount);
                return true;
            }
        }
            // countData(loopCount, comparisonCount);
            return false;
         }
    
    //Implementing Binary Search (No Recursion for counting)
    bool binarySearch(int array[], int size, int key,  int testNumber) {
        
        int loopCount = 0;
        int comparisonCount = 0;
        int low = 0;
        int high = size-1;
        
        while (low <= high) {
            loopCount++;
            int mid = (low + high)/2;
            if (array[mid] > key) {
                comparisonCount++;
               high = mid-1;
            }
            else if (array[mid] < key) {
                comparisonCount++;
                low = mid+1;
            }
            else if (array[mid] == key) {
                comparisonCount++;
                arrayLoop[testNumber] = loopCount;
                arrayCompare[testNumber] = comparisonCount;
                return true;
            }
        }
        arrayLoop[testNumber] = loopCount;
        arrayCompare[testNumber] = comparisonCount;
        return false;
    }
    
    //Implementing a method to print all counted data.
    void countData(int loopArray[], int compareArray[]) {
        
        int loopSum = 0;
        int comparSum = 0;
        int loopTotal = 0;
        int comparTotal = 0;
        
        for (int i = 0; i<sizeKey; i++) {
            loopSum += loopArray[i];
            comparSum += compareArray[i];
        }
        loopTotal = (loopSum/sizeKey);                  //For sequentialSearch and indexSequentialSearch
        comparTotal = (comparSum/sizeKey);
        cout << "Operations: " <<  3*(loopTotal)+2 + 8*(comparTotal);
        cout <<  " Total Found: " <<  countFound;
        cout <<  " Worst Case: " <<  loopTotal <<  endl;
        
        countFound = 0;
    }

    void clearTestData() {
        for (int i = 0; i<sizeKey; i++) {
            arrayLoop[i] = 0;
            arrayCompare[i] = 0;
        }
    }
    
    
    //TODO: Implement a sorting algorithm for binary search.
    
    
    int main() {
        
        /*
        cout << "Generating First Array..." << endl;
        arrayGen(array1, size1);
        cout << "Generating Second Array..." << endl;
        arrayGen(array2, size2);
        cout << "Generating Third Array (please wait)..." << endl;
        arrayGen(array3, size3);
        cout << "Generating Fourth Array (please wait)..." <<  endl;
        arrayGen(array4, size4);
        */
        
       // cout << "Generating Array with keys... \n" <<  endl;
       // arrayKeyGen(arrayKey,sizeKey);
        
        cout <<  " Searching First Array with Sequential Search. \n" <<  endl;
        for (int i = 0; i<tests; i++) {
            arrayGen(array1, size1);
            arrayKeyGen(arrayKey,sizeKey);
            for (int j = 0; j<sizeKey; j++) {
                sequentialSearch(array1, size1, arrayKey[j], j);
            }
            countData(arrayLoop, arrayCompare);
            clearTestData();
        }
        
        
        cout <<  "\n Searching Second Array with Sequential Search. \n" <<  endl;
        for (int i = 0; i<tests; i++) {
            arrayGen(array2, size2);
            arrayKeyGen(arrayKey,sizeKey);
            for (int j = 0; j<sizeKey; j++) {
                sequentialSearch(array2, size2, arrayKey[j], j);
            }
            countData(arrayLoop, arrayCompare);
            clearTestData();
        }
        
        cout << "\n Searching Third Array with Sequential Search. \n" << endl;
        for (int i = 0; i<tests; i++) {
            arrayGen(array3, size3);
            arrayKeyGen(arrayKey, sizeKey);
            for (int j = 0; j<sizeKey; j++) {
                sequentialSearchFirst(array3, size3, arrayKey[j], j);
            }
        }
        countData(arrayLoop, arrayCompare);
        clearTestData();
        
    }

    
    
