// Dead Code - Simple Crypto Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int key_length;
} SimpleCrypto;

SimpleCrypto* simple_crypto_create(const char* key) {
    SimpleCrypto* crypto = (SimpleCrypto*)malloc(sizeof(SimpleCrypto));
    if (crypto && key) {
        crypto->key_length = strlen(key);
        crypto->key = (char*)malloc(crypto->key_length + 1);
        if (crypto->key) {
            strcpy(crypto->key, key);
        }
    }
    return crypto;
}

void simple_crypto_xor_encrypt(SimpleCrypto* crypto, const char* plaintext, char* ciphertext, int length) {
    if (crypto && crypto->key && plaintext && ciphertext && length > 0) {
        for (int i = 0; i < length; i++) {
            ciphertext[i] = plaintext[i] ^ crypto->key[i % crypto->key_length];
        }
        ciphertext[length] = '\0';
    }
}

void simple_crypto_xor_decrypt(SimpleCrypto* crypto, const char* ciphertext, char* plaintext, int length) {
    if (crypto && crypto->key && ciphertext && plaintext && length > 0) {
        for (int i = 0; i < length; i++) {
            plaintext[i] = ciphertext[i] ^ crypto->key[i % crypto->key_length];
        }
        plaintext[length] = '\0';
    }
}

void simple_crypto_caesar_encrypt(SimpleCrypto* crypto, const char* plaintext, char* ciphertext, int shift) {
    if (crypto && plaintext && ciphertext) {
        int len = strlen(plaintext);
        for (int i = 0; i < len; i++) {
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
                ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
            } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
                ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
            } else {
                ciphertext[i] = plaintext[i];
            }
        }
        ciphertext[len] = '\0';
    }
}

void simple_crypto_caesar_decrypt(SimpleCrypto* crypto, const char* ciphertext, char* plaintext, int shift) {
    if (crypto && ciphertext && plaintext) {
        int len = strlen(ciphertext);
        for (int i = 0; i < len; i++) {
            if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                plaintext[i] = ((ciphertext[i] - 'A' - shift + 26) % 26) + 'A';
            } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                plaintext[i] = ((ciphertext[i] - 'a' - shift + 26) % 26) + 'a';
            } else {
                plaintext[i] = ciphertext[i];
            }
        }
        plaintext[len] = '\0';
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

