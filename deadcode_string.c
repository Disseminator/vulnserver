// Dead Code - String Processor Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char* buffer;
    int capacity;
    int length;
} StringProcessor;

StringProcessor* string_processor_create(int capacity) {
    StringProcessor* sp = (StringProcessor*)malloc(sizeof(StringProcessor));
    if (sp) {
        sp->capacity = capacity;
        sp->buffer = (char*)malloc(capacity);
        if (sp->buffer) {
            sp->buffer[0] = '\0';
            sp->length = 0;
        }
    }
    return sp;
}

void string_processor_append(StringProcessor* sp, const char* str) {
    if (sp && sp->buffer && str) {
        int str_len = strlen(str);
        if (sp->length + str_len < sp->capacity) {
            strcat(sp->buffer, str);
            sp->length += str_len;
        }
    }
}

void string_processor_to_upper(StringProcessor* sp) {
    if (sp && sp->buffer) {
        for (int i = 0; i < sp->length; i++) {
            sp->buffer[i] = toupper(sp->buffer[i]);
        }
    }
}

void string_processor_to_lower(StringProcessor* sp) {
    if (sp && sp->buffer) {
        for (int i = 0; i < sp->length; i++) {
            sp->buffer[i] = tolower(sp->buffer[i]);
        }
    }
}

int string_processor_reverse(StringProcessor* sp) {
    if (sp && sp->buffer && sp->length > 0) {
        int start = 0;
        int end = sp->length - 1;
        while (start < end) {
            char temp = sp->buffer[start];
            sp->buffer[start] = sp->buffer[end];
            sp->buffer[end] = temp;
            start++;
            end--;
        }
        return 1;
    }
    return 0;
}

void string_processor_clear(StringProcessor* sp) {
    if (sp && sp->buffer) {
        sp->buffer[0] = '\0';
        sp->length = 0;
    }
}

void string_processor_destroy(StringProcessor* sp) {
    if (sp) {
        if (sp->buffer) {
            free(sp->buffer);
        }
        free(sp);
    }
}

