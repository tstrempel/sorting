#include "sort_functions.h"

#define RECORD_LENGTH 50
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
    //füllt einen Speicherbereich, welche wir später als Array adressieren können mit Zufallszahlen
    for (int i = 0; i < *length; i++) {
        keys[i] = rand() % 70000;
    }

    return keys;
}

void free_bulk(int **record_array) {
    //wendet den Free Befehl auf elle Arrays in einem zweidimensionalen Array an

    for (size_t i = 0; i < RECORD_LENGTH; i++) {
        free(*(record_array + i));
    }
}

void sort_records(int **record_array, const int *length) {
    clock_t start, end;
    SortTimer times;

    times.selection_time = 0;
    times.insertion_time = 0;
    times.quick_time = 0;
    times.qsort_time = 0;


    /* Routine fuer Selectionsort bzw. Sortieren durch Auswahl */
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        start = clock();
        selection_sort(record_array[i], length);
        end = clock();

        /* Die durch clock() gemessene Zeit */
        times.selection_time_values[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
        times.selection_time += times.selection_time_values[i];

        if (PRINT_PROGRESS)
            printf("selectionsort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
    /* Berechnung der mittleren Zeit, um die totale Zeit zu erhalten auskommentieren */
    times.selection_time /= RECORD_LENGTH;


    // Routine fuer Insertionsort bzw. Sortieren durch Einfuegen
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        start = clock();
        insertion_sort(record_array[i], length);
        end = clock();

        times.insertion_time_values[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
        times.insertion_time += times.insertion_time_values[i];

        if (PRINT_PROGRESS)
            printf("Insertionsort\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
    times.insertion_time /= RECORD_LENGTH;


    // Routine fuer Quicksort
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        start = clock();
        quick_sort(record_array[i], 0, *length - 1);
        end = clock();

        times.quick_time_values[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
        times.quick_time += times.quick_time_values[i];

        if (PRINT_PROGRESS)
            printf("Quicksort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
    times.quick_time /= RECORD_LENGTH;


    // Routine fuer qsort (C-Bibliotheksfunktion)
    for (int i = 0; i < RECORD_LENGTH; i++) {
        record_array[i] = create_array(length);
    }
    for (int i = 0; i < RECORD_LENGTH; i++) {
        start = clock();
        /*qsort benötigt ein Array, dess Laenge, die Größe des Datentypes, und eine Vergleichsfunktion*/
        qsort(record_array[i], *length, sizeof(int), compare_function);
        end = clock();

        times.qsort_time_values[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
        times.qsort_time += times.qsort_time_values[i];

        if (PRINT_PROGRESS)
            printf("Quicksort\t\t Arraylaenge: %d  Datensatz Nummer: %d\n", *length, i);
    }
    free_bulk(record_array);
    times.qsort_time /= RECORD_LENGTH;


    printf("%f %f %f %f\n", times.selection_time, times.insertion_time, times.quick_time, times.qsort_time);

}

void run() {
    const int lengths[6] = {20, 100, 1000, 10000, 20000, 50000};
    const int *length_ptr = &lengths[0];

    int *records_20[RECORD_LENGTH];

    for (int i = 0; i < 3; i++) {
        records_20[i] = create_array(length_ptr);
    }
    selection_sort_verbose(records_20[0], length_ptr);
    insertion_sort_verbose(records_20[1], length_ptr);
    quick_sort_verbose(records_20[2], 0, 19);
    print_array(records_20[2], 0, 19, "Endergebnis Quicksort");

    free(records_20[0]);
    free(records_20[1]);
    free(records_20[2]);

    /* Berechnung des Laufzeitverhaltens */
    int *records_100[RECORD_LENGTH];
    sort_records(records_100, length_ptr+1);

    int *records_1000[RECORD_LENGTH];
    sort_records(records_1000, length_ptr+2);

    int *records_10000[RECORD_LENGTH];
    sort_records(records_10000, length_ptr+3);

    int *records_20000[RECORD_LENGTH];
    sort_records(records_20000, length_ptr+4);

    int *records_50000[RECORD_LENGTH];
    sort_records(records_50000, length_ptr+5);

}

int main() {
    /* nur einmal aufrufen, fuer die Zufallszahlen */
    srand((unsigned) time(NULL));
    run();

    return EXIT_SUCCESS;
}