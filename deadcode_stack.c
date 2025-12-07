// Dead Code - Stack Class
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

Stack* stack_create() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack) {
        stack->top = -1;
    }
    return stack;
}

int stack_push(Stack* stack, int value) {
    if (stack && stack->top < MAX_STACK_SIZE - 1) {
        stack->top++;
        stack->items[stack->top] = value;
        return 1;
    }
    return 0;
}

int stack_pop(Stack* stack) {
    if (stack && stack->top >= 0) {
        int value = stack->items[stack->top];
        stack->top--;
        return value;
    }
    return -1;
}

int stack_peek(Stack* stack) {
    if (stack && stack->top >= 0) {
        return stack->items[stack->top];
    }
    return -1;
}

int stack_is_empty(Stack* stack) {
    if (stack) {
        return stack->top == -1;
    }
    return 1;
}

int stack_is_full(Stack* stack) {
    if (stack) {
        return stack->top >= MAX_STACK_SIZE - 1;
    }
    return 0;
}

int stack_size(Stack* stack) {
    if (stack) {
        return stack->top + 1;
    }
    return 0;
}

void stack_clear(Stack* stack) {
    if (stack) {
        stack->top = -1;
    }
}

void stack_destroy(Stack* stack) {
    if (stack) {
        free(stack);
    }
}

