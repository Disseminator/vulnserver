// Dead Code - Sorting Algorithm Class
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    int size;
} Sorter;

Sorter* sorter_create(int* array, int size) {
    Sorter* sorter = (Sorter*)malloc(sizeof(Sorter));
    if (sorter) {
        sorter->size = size;
        sorter->array = (int*)malloc(size * sizeof(int));
        if (sorter->array) {
            for (int i = 0; i < size; i++) {
                sorter->array[i] = array[i];
            }
        }
    }
    return sorter;
}

void sorter_bubble_sort(Sorter* sorter) {
    if (sorter && sorter->array) {
        for (int i = 0; i < sorter->size - 1; i++) {
            for (int j = 0; j < sorter->size - i - 1; j++) {
                if (sorter->array[j] > sorter->array[j + 1]) {
                    int temp = sorter->array[j];
                    sorter->array[j] = sorter->array[j + 1];
                    sorter->array[j + 1] = temp;
                }
            }
        }
    }
}

static void sorter_quick_sort_recursive(int* arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        
        int pi = i + 1;
        sorter_quick_sort_recursive(arr, low, pi - 1);
        sorter_quick_sort_recursive(arr, pi + 1, high);
    }
}

void sorter_quick_sort(Sorter* sorter) {
    if (sorter && sorter->array && sorter->size > 0) {
        sorter_quick_sort_recursive(sorter->array, 0, sorter->size - 1);
    }
}

void sorter_selection_sort(Sorter* sorter) {
    if (sorter && sorter->array) {
        for (int i = 0; i < sorter->size - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < sorter->size; j++) {
                if (sorter->array[j] < sorter->array[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                int temp = sorter->array[i];
                sorter->array[i] = sorter->array[min_idx];
                sorter->array[min_idx] = temp;
            }
        }
    }
}

int* sorter_get_array(Sorter* sorter) {
    if (sorter) {
        return sorter->array;
    }
    return NULL;
}

int sorter_get_size(Sorter* sorter) {
    if (sorter) {
        return sorter->size;
    }
    return 0;
}

void sorter_destroy(Sorter* sorter) {
    if (sorter) {
        if (sorter->array) {
            free(sorter->array);
        }
        free(sorter);
    }
}

