
#include <libnet.h>
#include <time.h>
#include "sort.h"


/*
 * When running the program without args, it'll search for files 10.txt~10000000.txt under the folders random_int,asc_int and desc_int
 * respectively for random ordered arrays, ascending ordered arrays and descending ordered arrays
 */

enum sortTypes {
    BUBBLE,
    SELECTION,
    INSERTION,
    QUICK,
    MERGE
};

int *getArray(int type, int amount) {
    char str[25];
    switch (type) {
        case 1:
            sprintf(str, "random_int/%d.txt", amount);
            break;
        case 2:
            sprintf(str, "asc_int/%d.txt", amount);
            break;
        case 3:
            sprintf(str, "desc_int/%d.txt", amount);
            break;
        default:
            printf("Error getting the array!\n");
            return NULL;

    }
    printf("CARALHO %s", str);
    FILE *fp = fopen(str, "r");
    int *array = malloc(amount * sizeof(int));
    int i = 0;
    while (!feof(fp) && i < amount) {
        fscanf(fp, "%d", &array[i]);
        i++;
    }
    fclose(fp);
    return array;
}

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (((long long) tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

void saveArray(char *str, int *array, int size) {
    FILE *fp = fopen(str, "w");
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d ", array[i]);
    }
    fclose(fp);
}

void
saveInfo(char *str, long int clocks, long long time, unsigned long long int compare, unsigned long long int change) {
    FILE *fp = fopen(str, "w");
    fprintf(fp, "Comparações: %llu.\nTrocas:%llu.\nCycles of clock spent: %lu.\nTime spent: %llu ms.\n", compare,
            change, clocks, time);
    fclose(fp);
}

int *mergeSort_packed(int *array, unsigned long long int *compare, unsigned long long int *change, int size) {
    mergeSort(array, 0, size - 1, compare, change);
    return array;
}

void sortTest(int type, int amount, int sortType) {
    int *array;
    unsigned long long int compare = 0;
    unsigned long long int change = 0;
    long int start_clock;
    long int end_clock;
    long long start_time;
    long long end_time;
    char str[100];
    char str2[100];
    int *(*sort)(int *array2, unsigned long long int *compare2, unsigned long long int *change2, int size);
    switch (sortType) {
        case BUBBLE:
            sort = &bubbleSort;
            strcpy(str, "bubbleSort/");
            strcpy(str2, str);
            break;
        case SELECTION:
            sort = &selectionSort;
            strcpy(str, "selectionSort/");
            strcpy(str2, str);
            break;
        case INSERTION:
            sort = &insertionSort;
            strcpy(str, "insertionSort/");
            strcpy(str2, str);
            break;
        case QUICK:
            sort = &quickSort;
            strcpy(str, "quickSort/");
            strcpy(str2, str);
            break;
        case MERGE:
            sort = &mergeSort_packed;
            strcpy(str, "mergeSort/");
            strcpy(str2, str);
            break;
        default:
            printf("Problem: SORT TYPE NOT IDENTIFIED!\n");
            return;

    }
    array = getArray(type, amount);
    start_time = timeInMilliseconds();
    start_clock = clock();
    sort(array, &compare, &change, amount);
    end_clock = clock();
    end_time = timeInMilliseconds();


    switch (type) {
        case 1:
            sprintf(str, "%s%d_random", str2, amount);
            break;
        case 2:
            sprintf(str, "%s%d_ascending", str2, amount);
            break;
        case 3:
            sprintf(str, "%s%d_descending", str2, amount);
            break;
        default:
            printf("Error! %s\b \n", str2);
            return;

    }
    sprintf(str2, "%s_result.txt", str);
    sprintf(str, "%s.txt", str);

    saveArray(str, array, amount);
    saveInfo(str2, end_clock - start_clock, end_time - start_time, compare, change);
    free(array);
    printf("Done!\n");


}


void doTests(int sortType) {
    for (int i = 1; i < 4; i++) {
        switch (i) {
            case 1:
                printf("Random ordered:\n");
                break;
            case 2:
                printf("Ascending ordered:\n");
                break;
            case 3:
                printf("Descending ordered:\n");
                break;
            default:
                return;
        }

        for (int j = 10; j <= 1000000; j *= 10) {
            printf("Array of %d numbers... ", j);
            sortTest(i, j, sortType);
            if (j == 100000) {
                for (int k = j * 2; k <= 900000; k += j) {

                    printf("Array of %d numbers... ", k);
                    sortTest(i, k, sortType);

                }
            }
        }

    }
}


int main() {


    //BubbleSort
    printf("Starting tests for BubbleSort...\n");
    doTests(BUBBLE);
    printf("BubbleSort tests done!\n");
    //SelectionSort
    printf("Starting tests for SelectionSort...\n");
    doTests(SELECTION);
    printf("SelectionSort tests done!\n");
    //InsertionSort
    printf("Starting tests for InsertionSort...\n");
    doTests(INSERTION);
    printf("InsertionSort tests done!\n");
    //QuickSort
    printf("Starting tests for QuickSort...\n");
    doTests(QUICK);
    printf("QuickSort tests done!\n");
    //MergeSort
    printf("Starting tests for MergeSort...\n");
    doTests(MERGE);
    printf("MergeSort tests done!\n");





    //quickSort(array, &compare, &change, sizeof(array) / sizeof(int));
    //mergeSort(array, 0, (sizeof(array) / sizeof(int))-1, &compare, &change);
    //int* resultado = array;
    //for (int i = 0; i < sizeof(array) / sizeof(int); i++)
    //  printf("%d ", array[i]);
    /*for (int i = 0; i < sizeof(array) / sizeof(int); i++)
        printf("%d ", *(resultado + i));

    printf("\nTrocas Efetuadas: %d\nComparacoes: %d\n", change, compare);*/
    printf("Tudo Certo!\n");
    return 0;
}