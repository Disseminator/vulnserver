// Dead Code - Simple Parser Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char* input;
    int position;
    int length;
} Parser;

Parser* parser_create(const char* input) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    if (parser && input) {
        parser->length = strlen(input);
        parser->input = (char*)malloc(parser->length + 1);
        if (parser->input) {
            strcpy(parser->input, input);
            parser->position = 0;
        }
    }
    return parser;
}

int parser_peek(Parser* parser) {
    if (parser && parser->input && parser->position < parser->length) {
        return parser->input[parser->position];
    }
    return '\0';
}

int parser_consume(Parser* parser) {
    if (parser && parser->input && parser->position < parser->length) {
        return parser->input[parser->position++];
    }
    return '\0';
}

void parser_skip_whitespace(Parser* parser) {
    if (parser && parser->input) {
        while (parser->position < parser->length && isspace(parser->input[parser->position])) {
            parser->position++;
        }
    }
}

int parser_parse_integer(Parser* parser) {
    if (parser && parser->input) {
        parser_skip_whitespace(parser);
        int value = 0;
        int sign = 1;
        
        if (parser->position < parser->length && parser->input[parser->position] == '-') {
            sign = -1;
            parser->position++;
        }
        
        while (parser->position < parser->length && isdigit(parser->input[parser->position])) {
            value = value * 10 + (parser->input[parser->position] - '0');
            parser->position++;
        }
        
        return value * sign;
    }
    return 0;
}

int parser_parse_token(Parser* parser, char* buffer, int buffer_size) {
    if (parser && parser->input && buffer && buffer_size > 0) {
        parser_skip_whitespace(parser);
        int i = 0;
        
        while (parser->position < parser->length && 
               !isspace(parser->input[parser->position]) && 
               i < buffer_size - 1) {
            buffer[i++] = parser->input[parser->position++];
        }
        buffer[i] = '\0';
        return i > 0;
    }
    return 0;
}

int parser_is_eof(Parser* parser) {
    if (parser) {
        return parser->position >= parser->length;
    }
    return 1;
}

void parser_reset(Parser* parser) {
    if (parser) {
        parser->position = 0;
    }
}

void parser_destroy(Parser* parser) {
    if (parser) {
        if (parser->input) {
            free(parser->input);
        }
        free(parser);
    }
}

