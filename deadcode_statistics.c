// Dead Code - Statistics Calculator Class
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double* data;
    int size;
    int capacity;
} Statistics;

Statistics* statistics_create(int capacity) {
    Statistics* stats = (Statistics*)malloc(sizeof(Statistics));
    if (stats) {
        stats->capacity = capacity;
        stats->size = 0;
        stats->data = (double*)malloc(capacity * sizeof(double));
    }
    return stats;
}

void statistics_add(Statistics* stats, double value) {
    if (stats && stats->data && stats->size < stats->capacity) {
        stats->data[stats->size++] = value;
    }
}

double statistics_mean(Statistics* stats) {
    if (stats && stats->data && stats->size > 0) {
        double sum = 0.0;
        for (int i = 0; i < stats->size; i++) {
            sum += stats->data[i];
        }
        return sum / stats->size;
    }
    return 0.0;
}

double statistics_median(Statistics* stats) {
    if (stats && stats->data && stats->size > 0) {
        double* sorted = (double*)malloc(stats->size * sizeof(double));
        if (sorted) {
            for (int i = 0; i < stats->size; i++) {
                sorted[i] = stats->data[i];
            }
            
            for (int i = 0; i < stats->size - 1; i++) {
                for (int j = 0; j < stats->size - i - 1; j++) {
                    if (sorted[j] > sorted[j + 1]) {
                        double temp = sorted[j];
                        sorted[j] = sorted[j + 1];
                        sorted[j + 1] = temp;
                    }
                }
            }
            
            double median;
            if (stats->size % 2 == 0) {
                median = (sorted[stats->size / 2 - 1] + sorted[stats->size / 2]) / 2.0;
            } else {
                median = sorted[stats->size / 2];
            }
            
            free(sorted);
            return median;
        }
    }
    return 0.0;
}

double statistics_standard_deviation(Statistics* stats) {
    if (stats && stats->data && stats->size > 0) {
        double mean = statistics_mean(stats);
        double sum_squared_diff = 0.0;
        
        for (int i = 0; i < stats->size; i++) {
            double diff = stats->data[i] - mean;
            sum_squared_diff += diff * diff;
        }
        
        return sqrt(sum_squared_diff / stats->size);
    }
    return 0.0;
}

double statistics_min(Statistics* stats) {
    if (stats && stats->data && stats->size > 0) {
        double min = stats->data[0];
        for (int i = 1; i < stats->size; i++) {
            if (stats->data[i] < min) {
                min = stats->data[i];
            }
        }
        return min;
    }
    return 0.0;
}

double statistics_max(Statistics* stats) {
    if (stats && stats->data && stats->size > 0) {
        double max = stats->data[0];
        for (int i = 1; i < stats->size; i++) {
            if (stats->data[i] > max) {
                max = stats->data[i];
            }
        }
        return max;
    }
    return 0.0;
}

int statistics_size(Statistics* stats) {
    if (stats) {
        return stats->size;
    }
    return 0;
}

void statistics_clear(Statistics* stats) {
    if (stats) {
        stats->size = 0;
    }
}

void statistics_destroy(Statistics* stats) {
    if (stats) {
        if (stats->data) {
            free(stats->data);
        }
        free(stats);
    }
}

