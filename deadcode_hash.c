// Dead Code - Hash Table Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 101

typedef struct HashEntry {
    char* key;
    int value;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    HashEntry* buckets[HASH_TABLE_SIZE];
    int count;
} HashTable;

static unsigned int hash_function(const char* key) {
    unsigned int hash = 0;
    if (key) {
        for (int i = 0; key[i] != '\0'; i++) {
            hash = hash * 31 + key[i];
        }
    }
    return hash % HASH_TABLE_SIZE;
}

HashTable* hash_table_create() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table) {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            table->buckets[i] = NULL;
        }
        table->count = 0;
    }
    return table;
}

void hash_table_put(HashTable* table, const char* key, int value) {
    if (table && key) {
        unsigned int index = hash_function(key);
        HashEntry* entry = table->buckets[index];
        
        while (entry != NULL) {
            if (strcmp(entry->key, key) == 0) {
                entry->value = value;
                return;
            }
            entry = entry->next;
        }
        
        HashEntry* new_entry = (HashEntry*)malloc(sizeof(HashEntry));
        if (new_entry) {
            new_entry->key = (char*)malloc(strlen(key) + 1);
            if (new_entry->key) {
                strcpy(new_entry->key, key);
                new_entry->value = value;
                new_entry->next = table->buckets[index];
                table->buckets[index] = new_entry;
                table->count++;
            }
        }
    }
}

int hash_table_get(HashTable* table, const char* key) {
    if (table && key) {
        unsigned int index = hash_function(key);
        HashEntry* entry = table->buckets[index];
        
        while (entry != NULL) {
            if (strcmp(entry->key, key) == 0) {
                return entry->value;
            }
            entry = entry->next;
        }
    }
    return -1;
}

int hash_table_remove(HashTable* table, const char* key) {
    if (table && key) {
        unsigned int index = hash_function(key);
        HashEntry* entry = table->buckets[index];
        HashEntry* prev = NULL;
        
        while (entry != NULL) {
            if (strcmp(entry->key, key) == 0) {
                if (prev) {
                    prev->next = entry->next;
                } else {
                    table->buckets[index] = entry->next;
                }
                int value = entry->value;
                free(entry->key);
                free(entry);
                table->count--;
                return value;
            }
            prev = entry;
            entry = entry->next;
        }
    }
    return -1;
}

int hash_table_size(HashTable* table) {
    if (table) {
        return table->count;
    }
    return 0;
}

void hash_table_clear(HashTable* table) {
    if (table) {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            HashEntry* entry = table->buckets[i];
            while (entry != NULL) {
                HashEntry* next = entry->next;
                free(entry->key);
                free(entry);
                entry = next;
            }
            table->buckets[i] = NULL;
        }
        table->count = 0;
    }
}

void hash_table_destroy(HashTable* table) {
    if (table) {
        hash_table_clear(table);
        free(table);
    }
}

