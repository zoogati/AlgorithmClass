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

//Default vaules for program

const int size1 = 100;
const int size2 = 10000;
const int size3 = 1000000;

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

//Function for generating random integer array (Doesn't matter if not-unique)
    void arrayGen(int array[], int size) {
        
        for (int i = 0; i < size; i++) {
            int element = rand() % (2*size);
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
        
        for (int i = size; i < 0; i--) {
            array[i-1] = i;
        }
    }
    
//Implementing Straight Insertion Sort
    void insertionSort(int array[],int size) {
        
        for (int i = 