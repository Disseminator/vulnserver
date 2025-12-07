// Dead Code - Math Calculator Class
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double value;
    int precision;
} MathCalculator;

MathCalculator* math_calculator_create(double initial_value) {
    MathCalculator* calc = (MathCalculator*)malloc(sizeof(MathCalculator));
    if (calc) {
        calc->value = initial_value;
        calc->precision = 2;
    }
    return calc;
}

void math_calculator_add(MathCalculator* calc, double num) {
    if (calc) {
        calc->value += num;
    }
}

void math_calculator_multiply(MathCalculator* calc, double num) {
    if (calc) {
        calc->value *= num;
    }
}

double math_calculator_get_square_root(MathCalculator* calc) {
    if (calc && calc->value >= 0) {
        return sqrt(calc->value);
    }
    return 0.0;
}

double math_calculator_get_power(MathCalculator* calc, double exponent) {
    if (calc) {
        return pow(calc->value, exponent);
    }
    return 0.0;
}

void math_calculator_reset(MathCalculator* calc) {
    if (calc) {
        calc->value = 0.0;
    }
}

void math_calculator_destroy(MathCalculator* calc) {
    if (calc) {
        free(calc);
    }
}

