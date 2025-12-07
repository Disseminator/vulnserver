// Dead Code - Dynamic Array Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int* data;
    int size;
    int capacity;
} DynamicArray;

DynamicArray* dynamic_array_create() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (arr) {
        arr->capacity = INITIAL_CAPACITY;
        arr->size = 0;
        arr->data = (int*)malloc(arr->capacity * sizeof(int));
    }
    return arr;
}

static void dynamic_array_resize(DynamicArray* arr) {
    if (arr && arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    }
}

void dynamic_array_append(DynamicArray* arr, int value) {
    if (arr) {
        dynamic_array_resize(arr);
        if (arr->data) {
            arr->data[arr->size] = value;
            arr->size++;
        }
    }
}

int dynamic_array_get(DynamicArray* arr, int index) {
    if (arr && arr->data && index >= 0 && index < arr->size) {
        return arr->data[index];
    }
    return -1;
}

void dynamic_array_set(DynamicArray* arr, int index, int value) {
    if (arr && arr->data && index >= 0 && index < arr->size) {
        arr->data[index] = value;
    }
}

int dynamic_array_size(DynamicArray* arr) {
    if (arr) {
        return arr->size;
    }
    return 0;
}

int dynamic_array_capacity(DynamicArray* arr) {
    if (arr) {
        return arr->capacity;
    }
    return 0;
}

void dynamic_array_clear(DynamicArray* arr) {
    if (arr) {
        arr->size = 0;
    }
}

int dynamic_array_find(DynamicArray* arr, int value) {
    if (arr && arr->data) {
        for (int i = 0; i < arr->size; i++) {
            if (arr->data[i] == value) {
                return i;
            }
        }
    }
    return -1;
}

void dynamic_array_destroy(DynamicArray* arr) {
    if (arr) {
        if (arr->data) {
            free(arr->data);
        }
        free(arr);
    }
}

