// Dead Code - Min Heap Class
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* min_heap_create(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap) {
        heap->capacity = capacity > MAX_HEAP_SIZE ? MAX_HEAP_SIZE : capacity;
        heap->size = 0;
        heap->data = (int*)malloc((size_t)heap->capacity * sizeof(int));
        if (!heap->data) {
            free(heap);
            return NULL;
        }
    }
    return heap;
}

static void heap_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heap_heapify_up(MinHeap* heap, int index) {
    if (heap && index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[parent] > heap->data[index]) {
            heap_swap(&heap->data[parent], &heap->data[index]);
            heap_heapify_up(heap, parent);
        }
    }
}

static void heap_heapify_down(MinHeap* heap, int index) {
    if (heap) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        
        if (smallest != index) {
            heap_swap(&heap->data[index], &heap->data[smallest]);
            heap_heapify_down(heap, smallest);
        }
    }
}

void min_heap_insert(MinHeap* heap, int value) {
    if (heap && heap->data && heap->size < heap->capacity) {
        heap->data[heap->size] = value;
        heap_heapify_up(heap, heap->size);
        heap->size++;
    }
}

int min_heap_extract_min(MinHeap* heap) {
    if (heap && heap->data && heap->size > 0) {
        int min = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heap_heapify_down(heap, 0);
        return min;
    }
    return -1;
}

int min_heap_peek(MinHeap* heap) {
    if (heap && heap->data && heap->size > 0) {
        return heap->data[0];
    }
    return -1;
}

int min_heap_size(MinHeap* heap) {
    if (heap) {
        return heap->size;
    }
    return 0;
}

int min_heap_is_empty(MinHeap* heap) {
    if (heap) {
        return heap->size == 0;
    }
    return 1;
}

void min_heap_destroy(MinHeap* heap) {
    if (heap) {
        if (heap->data) {
            free(heap->data);
        }
        free(heap);
    }
}

