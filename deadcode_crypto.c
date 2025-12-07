// Dead Code - Simple Crypto Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int key_length;
} SimpleCrypto;

SimpleCrypto* simple_crypto_create(const char* key) {
    if (!key) {
        return NULL;
    }
    SimpleCrypto* crypto = (SimpleCrypto*)malloc(sizeof(SimpleCrypto));
    if (crypto) {
        size_t key_len = strlen(key);
        if (key_len == 0 || key_len > 1000) {
            free(crypto);
            return NULL;
        }
        crypto->key_length = (int)key_len;
        crypto->key = (char*)malloc(key_len + 1);
        if (crypto->key) {
            strncpy(crypto->key, key, key_len);
            crypto->key[key_len] = '\0';
        } else {
            free(crypto);
            return NULL;
        }
    }
    return crypto;
}

void simple_crypto_xor_encrypt(SimpleCrypto* crypto, const char* plaintext, char* ciphertext, int length) {
    if (crypto && crypto->key && crypto->key_length > 0 && plaintext && ciphertext && length > 0 && length <= 10000) {
        for (int i = 0; i < length; i++) {
            ciphertext[i] = plaintext[i] ^ crypto->key[i % crypto->key_length];
        }
        if (length < 10000) {
            ciphertext[length] = '\0';
        }
    }
}

void simple_crypto_xor_decrypt(SimpleCrypto* crypto, const char* ciphertext, char* plaintext, int length) {
    if (crypto && crypto->key && crypto->key_length > 0 && ciphertext && plaintext && length > 0 && length <= 10000) {
        for (int i = 0; i < length; i++) {
            plaintext[i] = ciphertext[i] ^ crypto->key[i % crypto->key_length];
        }
        if (length < 10000) {
            plaintext[length] = '\0';
        }
    }
}

void simple_crypto_caesar_encrypt(SimpleCrypto* crypto, const char* plaintext, char* ciphertext, int shift) {
    if (crypto && plaintext && ciphertext) {
        size_t len = strlen(plaintext);
        if (len > 0 && len <= 10000) {
            int normalized_shift = shift % 26;
            if (normalized_shift < 0) {
                normalized_shift += 26;
            }
            for (size_t i = 0; i < len; i++) {
                if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
                    ciphertext[i] = ((plaintext[i] - 'A' + normalized_shift) % 26) + 'A';
                } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
                    ciphertext[i] = ((plaintext[i] - 'a' + normalized_shift) % 26) + 'a';
                } else {
                    ciphertext[i] = plaintext[i];
                }
            }
            ciphertext[len] = '\0';
        }
    }
}

void simple_crypto_caesar_decrypt(SimpleCrypto* crypto, const char* ciphertext, char* plaintext, int shift) {
    if (crypto && ciphertext && plaintext) {
        size_t len = strlen(ciphertext);
        if (len > 0 && len <= 10000) {
            int normalized_shift = shift % 26;
            if (normalized_shift < 0) {
                normalized_shift += 26;
            }
            for (size_t i = 0; i < len; i++) {
                if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                    plaintext[i] = ((ciphertext[i] - 'A' - normalized_shift + 26) % 26) + 'A';
                } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                    plaintext[i] = ((ciphertext[i] - 'a' - normalized_shift + 26) % 26) + 'a';
                } else {
                    plaintext[i] = ciphertext[i];
                }
            }
            plaintext[len] = '\0';
        }
    }
}

void simple_crypto_destroy(SimpleCrypto* crypto) {
    if (crypto) {
        if (crypto->key) {
            free(crypto->key);
        }
        free(crypto);
    }
}

