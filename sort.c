//
// Created by nowayrlz on 03/10/17.
//


#include "sort.h"


int *bubbleSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size) {

    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            (*compare)++;
            if (*(array + j) > *(array + j + 1)) {
                (*change)++;
                swap(&array[j], &array[j+1]);
            }
        }
    }
    return array;
}

int *selectionSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size) {
    int aux;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            (*compare)++;
            if (*(array + i) > *(array + j)) {
                (*change)++;
                aux = *(array + i);
                *(array + i) = *(array + j);
                *(array + j) = aux;
            }
        }
    }
    return array;
}


int *insertionSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size) {

    int i, key, j;
    for (i = 1; i < size; i++)
    {
        key = array[i];
        j = i-1;


        while (j >= 0 && array[j] > key)
        {
            (*compare)++;
            (*change)++;
            array[j+1] = array[j];
            j = j-1;
        }
        (*change)++;
        array[j+1] = key;
    }
    return array;
}



static inline void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void randomizeArray(int *array, int size) {
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        swap(&array[rand() % size], &array[rand() % size]);

    }
}

int *quickSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size) {
    if (size <= 1) return array;

    if (*compare == 0)
        randomizeArray(array, size);

    int pivot = *(array + size - 1);
    int p1 = 0;

    for (int i = 0; i < size - 1; i++) {
        (*compare)++;
        if (array[i] < pivot) {
            (*change)++;
            swap(&array[i], &array[p1]);
            p1++;
        }
    }
    (*change)++;
    swap(&array[size - 1], &array[p1]);

    quickSort(&array[p1 + 1], compare, change, size - (p1 + 1));
    quickSort(&array[0], compare, change, p1);


    return array;

}

int *heapSort(int *array, unsigned long long int *compare, unsigned long long int *change, int size) {
    int i = size / 2;
    int pai;
    int filho;
    int t;
    while (1) {
        if (i > 0) {
            i--;
            t = array[i];
        } else {
            size--;
            if (size == 0) return array;
            t = array[size];
            array[size] = array[0];
        }
        pai = i;
        filho = i * 2 + 1;
        while (filho < size) {
            if ((filho + 1 < size) && (array[filho + 1] > array[filho]))
                filho++;
            if (array[filho] > t) {
                array[pai] = array[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        array[pai] = t;
    }
}

void merge(int arr[], int l, int m, int r, unsigned long long int *compare, unsigned long long int *change) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int *L = (int *) malloc(n1 * sizeof(int));
    int *R = (int *) malloc(n2 * sizeof(int));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        //(*change)++;
    }

    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        //(*change)++;
    }


    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        (*compare)++;
        (*change)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        (*change)++;
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        (*change)++;
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

/*void mergeSort(int* array, int* compare, int* change, int size)
{
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
    if(size > 1)
    {


        size -= 1;
        int m = (size)/2;

        // Sort first and second halves
        mergeSort(array, compare, change, m);
        mergeSort(&array[m], compare, change, size-m);

        merge(array, 0, m, size);
    }

}*/

int *mergeSort(int arr[], int l, int r, unsigned long long int *compare, unsigned long long int *change) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, compare, change);
        mergeSort(arr, m + 1, r, compare, change);

        merge(arr, l, m, r, compare, change);
    }
    return arr;
}