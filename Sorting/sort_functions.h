//
// Created by strempel on 23.12.17.
//

#ifndef AUD_SORT_FUNCTIONS_H
#define AUD_SORT_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare_function(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void print_array(int *keys, int begin, int end, char extra[]) {
    /* gibt einen Array von der Position Begin bis zur Position end aus
     * extra wird zur Verdeutlichung des aktuell laufenden Alogrithmus verwendet
     * */

    int length = end - begin + 1;
    printf("%s Laenge: %d\n", extra, length);

    for (int i = begin; i <= end; i++) {
        printf("%d ",keys[i]);
    }

    printf("\n\n");
}

void swap(int *pos1, int *pos2) {
    int swap = *pos1;
    *pos1 = *pos2;
    *pos2 = swap;
}

void selection_sort(int *keys, const int *length) {
    int low, element;
    low = 0;

    while (low < *length-1) {
        element = low;
        for (int i = low+1; i < *length-1; i++) {
            if (keys[i] < keys[element])
                element = i;
        }
        swap(keys+element, keys+low);
        ++low;
    }
}

void insertion_sort(int *keys, const int *length) {
    int i, j, value;

    for (i = 1; i < *length; i++) {
        value = keys[i];
        j = i;

        while (j > 0 && keys[j-1] > value) {
            keys[j] = keys[j-1];
            --j;
        }

        keys[j] = value;
    }
}

void quick_sort(int *keys, int begin, int end) {
    int i, j, pivot, pivot_value;
    i = begin;
    j = end;
    pivot = begin;
    pivot_value = keys[pivot];

    do {
        while (keys[i] < pivot_value)
            i++;

        while (keys[j] > pivot_value)
            j--;

        if (i > j)
            break;

        swap(keys+i, keys+j);

    } while (++i <= --j);

    if(begin < j)
        quick_sort(keys, begin, j);
    if(i < end)
        quick_sort(keys, i, end);


}

void selection_sort_verbose(int *keys, const int *length) {
    int low, element;
    low = 0;

    while (low < *length) {
        element = low;
        for (int i = low+1; i < *length; i++) {
            if (keys[i] < keys[element])
                element = i;
        }
        swap(&keys[element], &keys[low]);
        print_array(keys, 0, *length-1, "Selectionsort");
        ++low;
    }

    printf("-------------------------------------------------------------------------------------------------------\n");
}

void insertion_sort_verbose(int *keys, const int *length) {
    int i, j, value;

    for (i = 1; i < *length; i++) {
        value = keys[i];
        j = i;

        while (j > 0 && keys[j-1] > value) {
            keys[j] = keys[j-1];
            --j;
        }

        keys[j] = value;
        print_array(keys, 0, *length-1, "Insertionsort");
    }

    printf("-------------------------------------------------------------------------------------------------------\n");
}

void quick_sort_verbose(int *keys, int begin, int end) {
    int i, j, pivot, pivot_value;
    i = begin;
    j = end;
    pivot = begin;
    pivot_value = keys[pivot];

    printf("Pivot: Stelle %d Wert %d\n", pivot, keys[pivot]);
    print_array(keys, begin, end, "Quicksort-Start");

    do {
        while (keys[i] < pivot_value)
            i++;

        while (keys[j] > pivot_value)
            j--;

        if (i > j)
            break;

        swap(keys+i, keys+j);

    } while (++i <= --j);

    print_array(keys, begin, end, "Quicksort-Ende");
    printf("----------\n");

    if (begin == 0 && end == 19)
        printf("-------------------------linke Seite-------------------------\n\n");
    if(begin < j)
        quick_sort_verbose(keys, begin, j);
    if (begin == 0 && end == 19)
        printf("-------------------------rechte Seite-------------------------\n\n");
    if(i < end)
        quick_sort_verbose(keys, i, end);


}

#endif //AUD_SORT_FUNCTIONS_H
