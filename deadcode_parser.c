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
    if (!input) {
        return NULL;
    }
    size_t input_len = strlen(input);
    if (input_len > 100000) {
        return NULL;
    }
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    if (parser) {
        parser->length = (int)input_len;
        parser->input = (char*)malloc(input_len + 1);
        if (parser->input) {
            strncpy(parser->input, input, input_len);
            parser->input[input_len] = '\0';
            parser->position = 0;
        } else {
            free(parser);
            return NULL;
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
        long long value = 0;
        int sign = 1;
        
        if (parser->position < parser->length && parser->input[parser->position] == '-') {
            sign = -1;
            parser->position++;
        }
        
        int digits = 0;
        while (parser->position < parser->length && isdigit(parser->input[parser->position]) && digits < 10) {
            value = value * 10 + (parser->input[parser->position] - '0');
            parser->position++;
            digits++;
            if (value > 2147483647LL) {
                return 0;
            }
        }
        
        long long result = value * sign;
        if (result > 2147483647LL || result < -2147483648LL) {
            return 0;
        }
        return (int)result;
    }
    return 0;
}

int parser_parse_token(Parser* parser, char* buffer, int buffer_size) {
    if (parser && parser->input && buffer && buffer_size > 0 && buffer_size <= 10000) {
        parser_skip_whitespace(parser);
        int i = 0;
        
        while (parser->position < parser->length && 
               !isspace(parser->input[parser->position]) && 
               i < buffer_size - 1) {
            buffer[i++] = parser->input[parser->position++];
        }
        if (i < buffer_size) {
            buffer[i] = '\0';
        } else {
            buffer[buffer_size - 1] = '\0';
        }
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

