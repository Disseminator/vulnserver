// Dead Code - Validator Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int min_length;
    int max_length;
    int require_uppercase;
    int require_lowercase;
    int require_digit;
    int require_special;
} Validator;

Validator* validator_create(int min_length, int max_length) {
    Validator* validator = (Validator*)malloc(sizeof(Validator));
    if (validator) {
        validator->min_length = min_length;
        validator->max_length = max_length;
        validator->require_uppercase = 0;
        validator->require_lowercase = 0;
        validator->require_digit = 0;
        validator->require_special = 0;
    }
    return validator;
}

void validator_set_requirements(Validator* validator, int uppercase, int lowercase, int digit, int special) {
    if (validator) {
        validator->require_uppercase = uppercase;
        validator->require_lowercase = lowercase;
        validator->require_digit = digit;
        validator->require_special = special;
    }
}

int validator_validate_string(Validator* validator, const char* str) {
    if (validator && str) {
        int len = strlen(str);
        if (len < validator->min_length || len > validator->max_length) {
            return 0;
        }
        
        int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
        
        for (int i = 0; str[i] != '\0'; i++) {
            if (isupper(str[i])) {
                has_upper = 1;
            } else if (islower(str[i])) {
                has_lower = 1;
            } else if (isdigit(str[i])) {
                has_digit = 1;
            } else if (!isalnum(str[i])) {
                has_special = 1;
            }
        }
        
        if (validator->require_uppercase && !has_upper) return 0;
        if (validator->require_lowercase && !has_lower) return 0;
        if (validator->require_digit && !has_digit) return 0;
        if (validator->require_special && !has_special) return 0;
        
        return 1;
    }
    return 0;
}

int validator_validate_email(const char* email) {
    if (email) {
        int len = strlen(email);
        int at_pos = -1;
        int dot_pos = -1;
        
        for (int i = 0; i < len; i++) {
            if (email[i] == '@') {
                if (at_pos != -1) return 0;
                at_pos = i;
            } else if (email[i] == '.' && at_pos != -1) {
                dot_pos = i;
            }
        }
        
        return (at_pos > 0 && dot_pos > at_pos + 1 && dot_pos < len - 1);
    }
    return 0;
}

int validator_validate_number(const char* str, int min, int max) {
    if (str) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (!isdigit(str[i]) && str[i] != '-') {
                return 0;
            }
        }
        int num = atoi(str);
        return (num >= min && num <= max);
    }
    return 0;
}

int validator_validate_phone(const char* phone) {
    if (phone) {
        int digit_count = 0;
        for (int i = 0; phone[i] != '\0'; i++) {
            if (isdigit(phone[i])) {
                digit_count++;
            } else if (phone[i] != '-' && phone[i] != ' ' && phone[i] != '(' && phone[i] != ')') {
                return 0;
            }
        }
        return (digit_count >= 10 && digit_count <= 15);
    }
    return 0;
}

void validator_destroy(Validator* validator) {
    if (validator) {
        free(validator);
    }
}

