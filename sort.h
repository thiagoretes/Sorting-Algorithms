//
// Created by nowayrlz on 03/10/17.
//

#ifndef TRABALHO_SORTING_INT_SORT_H
#define TRABALHO_SORTING_INT_SORT_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif //TRABALHO_SORTING_INT_SORT_H

int *bubbleSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size);
int *selectionSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size);
int *insertionSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size);
static inline void swap(int* a, int* b);
int *quickSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size);
int* heapSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size);
int* mergeSort(int arr[], int l, int r, unsigned long long int* compare, unsigned long long int* change);
void merge(int arr[], int l, int m, int r, unsigned long long int* compare, unsigned long long int* change);
