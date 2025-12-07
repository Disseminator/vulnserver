// Dead Code - Cache Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CACHE_SIZE 100

typedef struct CacheEntry {
    char* key;
    void* value;
    int value_size;
    struct CacheEntry* next;
} CacheEntry;

typedef struct {
    CacheEntry* entries[MAX_CACHE_SIZE];
    int count;
    int max_size;
} Cache;

static unsigned int cache_hash(const char* key) {
    unsigned int hash = 0;
    if (key) {
        for (int i = 0; key[i] != '\0'; i++) {
            hash = hash * 31 + key[i];
        }
    }
    return hash % MAX_CACHE_SIZE;
}

Cache* cache_create(int max_size) {
    Cache* cache = (Cache*)malloc(sizeof(Cache));
    if (cache) {
        for (int i = 0; i < MAX_CACHE_SIZE; i++) {
            cache->entries[i] = NULL;
        }
        cache->count = 0;
        cache->max_size = max_size > 0 ? max_size : MAX_CACHE_SIZE;
    }
    return cache;
}

int cache_put(Cache* cache, const char* key, void* value, int value_size) {
    if (cache && key && value && value_size > 0) {
        if (cache->count >= cache->max_size) {
            return 0;
        }
        
        unsigned int index = cache_hash(key);
        size_t key_len = strlen(key);
        if (key_len > 1000) {
            return 0;
        }
        CacheEntry* entry = (CacheEntry*)malloc(sizeof(CacheEntry));
        if (entry) {
            entry->key = (char*)malloc(key_len + 1);
            if (entry->key) {
                strncpy(entry->key, key, key_len);
                entry->key[key_len] = '\0';
                if (value_size > 0 && value_size <= 100000) {
                    entry->value = malloc((size_t)value_size);
                    if (entry->value) {
                        memcpy(entry->value, value, (size_t)value_size);
                        entry->value_size = value_size;
                        entry->next = cache->entries[index];
                        cache->entries[index] = entry;
                        cache->count++;
                        return 1;
                    }
                }
                free(entry->key);
            }
            free(entry);
        }
    }
    return 0;
}

void* cache_get(Cache* cache, const char* key, int* value_size) {
    if (cache && key) {
        unsigned int index = cache_hash(key);
        CacheEntry* entry = cache->entries[index];
        
        while (entry != NULL) {
            if (strcmp(entry->key, key) == 0) {
                if (value_size) {
                    *value_size = entry->value_size;
                }
                return entry->value;
            }
            entry = entry->next;
        }
    }
    return NULL;
}

int cache_remove(Cache* cache, const char* key) {
    if (cache && key) {
        unsigned int index = cache_hash(key);
        CacheEntry* entry = cache->entries[index];
        CacheEntry* prev = NULL;
        
        while (entry != NULL) {
            if (strcmp(entry->key, key) == 0) {
                if (prev) {
                    prev->next = entry->next;
                } else {
                    cache->entries[index] = entry->next;
                }
                free(entry->key);
                free(entry->value);
                free(entry);
                cache->count--;
                return 1;
            }
            prev = entry;
            entry = entry->next;
        }
    }
    return 0;
}

int cache_size(Cache* cache) {
    if (cache) {
        return cache->count;
    }
    return 0;
}

void cache_clear(Cache* cache) {
    if (cache) {
        for (int i = 0; i < MAX_CACHE_SIZE; i++) {
            CacheEntry* entry = cache->entries[i];
            while (entry != NULL) {
                CacheEntry* next = entry->next;
                free(entry->key);
                free(entry->value);
                free(entry);
                entry = next;
            }
            cache->entries[i] = NULL;
        }
        cache->count = 0;
    }
}

void cache_destroy(Cache* cache) {
    if (cache) {
        cache_clear(cache);
        free(cache);
    }
}

