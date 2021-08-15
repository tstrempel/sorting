#include "sort_functions.h"

#define RECORD_LENGTH 100
#define PRINT_PROGRESS 0

int* create_array(const int *length) {

    if (*length == 0)
        return NULL;

    int *keys = (int*) malloc(*length * sizeof(int));
    // füllt einen Speicherbereich, welche wir später als Array adressieren können mit Zufallszahlen
    for (int i = 0; i < *length; i++) {
        keys[i] = rand() % 70000;
    }

    return keys;
}

void free_bulk(int **record_array) {
    // wendet den Free Befehl auf elle Arrays in einem zweidimensionalen Array an

    for (size_t i = 0; i < RECORD_LENGTH; i++) {
        free(*(record_array + i));
    }
}

void sort_records_selection_sort(int **record_array, const int *length) {
    /* Routine fuer Selectionsort bzw. Sortieren durch Auswahl */
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        selection_sort(record_array[i], length);

        if (PRINT_PROGRESS)
            printf("selectionsort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
}

void sort_records_insertion_sort(int **record_array, const int *length) {
    /* Routine fuer Selectionsort bzw. Sortieren durch Auswahl */
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        insertion_sort(record_array[i], length);

        if (PRINT_PROGRESS)
            printf("selectionsort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
}

void sort_records_quick_sort(int **record_array, const int *length) {
    /* Routine fuer Selectionsort bzw. Sortieren durch Auswahl */
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        quick_sort(record_array[i], 0, *length - 1);

        if (PRINT_PROGRESS)
            printf("selectionsort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
}

void sort_records_qsort(int **record_array, const int *length) {
    // Routine fuer qsort (C-Bibliotheksfunktion)
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        /*qsort benötigt ein Array, dess Laenge, die Größe des Datentypes, und eine Vergleichsfunktion*/
        qsort(record_array[i], *length, sizeof(int), compare_function);

        if (PRINT_PROGRESS)
            printf("Quicksort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
}

void run(int sort_type, int length) {
    /* Berechnung des Laufzeitverhaltens */
    int *records[RECORD_LENGTH];

    switch(sort_type) {
        case 0: sort_records_selection_sort(records, &length); break;
        case 1: sort_records_insertion_sort(records, &length); break;
        case 2: sort_records_quick_sort(records, &length); break;
        case 3: sort_records_qsort(records, &length); break;
    }
}

int main(int argc, char **argv) {
    /* arguments: 
     * 0,1,2 -> selectionsort, insertionsort, quicksort
     * int -> length of array to sort
     */
    /* nur einmal aufrufen, fuer die Zufallszahlen */
    srand((unsigned) time(NULL));
    
    run(atoi(argv[1]), atoi(argv[2]));

    return EXIT_SUCCESS;
}