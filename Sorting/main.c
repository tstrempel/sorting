#include "sort_functions.h"

#define RECORD_LENGTH 100
#define PRINT_PROGRESS 0

struct sort_timer_t {
  double selection_time;
  double insertion_time;
  double quick_time;
  double qsort_time;
  double selection_time_values[RECORD_LENGTH];
  double insertion_time_values[RECORD_LENGTH];
  double quick_time_values[RECORD_LENGTH];
  double qsort_time_values[RECORD_LENGTH];
};
typedef struct sort_timer_t SortTimer;

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

void sort_records(int **record_array, const int *length) {

}

double sort_records_selection_sort(int **record_array, const int *length) {
    clock_t start, end;
    double time = 0.0;
    double selection_time_values[RECORD_LENGTH];

    /* Routine fuer Selectionsort bzw. Sortieren durch Auswahl */
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        start = clock();
        selection_sort(record_array[i], length);
        end = clock();

        /* Die durch clock() gemessene Zeit */
        selection_time_values[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
        time += selection_time_values[i];

        if (PRINT_PROGRESS)
            printf("selectionsort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
    /* Berechnung der mittleren Zeit, um die totale Zeit zu erhalten auskommentieren */
    time /= RECORD_LENGTH;

    return time;
}

double sort_records_insertion_sort(int **record_array, const int *length) {
    clock_t start, end;
    double time = 0.0;
    double selection_time_values[RECORD_LENGTH];

    /* Routine fuer Selectionsort bzw. Sortieren durch Auswahl */
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        start = clock();
        insertion_sort(record_array[i], length);
        end = clock();

        /* Die durch clock() gemessene Zeit */
        selection_time_values[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
        time += selection_time_values[i];

        if (PRINT_PROGRESS)
            printf("selectionsort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
    /* Berechnung der mittleren Zeit, um die totale Zeit zu erhalten auskommentieren */
    time /= RECORD_LENGTH;

    return time;
}

double sort_records_quick_sort(int **record_array, const int *length) {
    clock_t start, end;
    double time = 0.0;
    double selection_time_values[RECORD_LENGTH];

    /* Routine fuer Selectionsort bzw. Sortieren durch Auswahl */
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        start = clock();
        quick_sort(record_array[i], 0, *length - 1);
        end = clock();

        /* Die durch clock() gemessene Zeit */
        selection_time_values[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
        time += selection_time_values[i];

        if (PRINT_PROGRESS)
            printf("selectionsort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
    /* Berechnung der mittleren Zeit, um die totale Zeit zu erhalten auskommentieren */
    time /= RECORD_LENGTH;

    return time;
}

double sort_records_qsort(int **record_array, const int *length) {
    clock_t start, end;
    double time = 0.0;
    double time_values[RECORD_LENGTH];

    // Routine fuer qsort (C-Bibliotheksfunktion)
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        start = clock();
        /*qsort benötigt ein Array, dess Laenge, die Größe des Datentypes, und eine Vergleichsfunktion*/
        qsort(record_array[i], *length, sizeof(int), compare_function);
        end = clock();

        time_values[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
        time += time_values[i];

        if (PRINT_PROGRESS)
            printf("Quicksort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
    time /= RECORD_LENGTH;

    return 0.0;
}

void run(int sort_type, int length) {
    /* Berechnung des Laufzeitverhaltens */
    int *records[RECORD_LENGTH];
    double time = 0.0;

    switch(sort_type) {
        case 0: time = sort_records_selection_sort(records, &length); break;
        case 1: time = sort_records_insertion_sort(records, &length); break;
        case 2: time = sort_records_quick_sort(records, &length); break;
        case 3: time = sort_records_qsort(records, &length); break;
        default: printf("Nothing was executed"); break;
    }

    printf("Time: %fs\n", time);
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