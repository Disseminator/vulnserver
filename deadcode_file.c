// Dead Code - File Manager Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    FILE* file;
    char* filename;
    int is_open;
} FileManager;

FileManager* file_manager_create(const char* filename) {
    FileManager* fm = (FileManager*)malloc(sizeof(FileManager));
    if (fm && filename) {
        fm->filename = (char*)malloc(strlen(filename) + 1);
        if (fm->filename) {
            strcpy(fm->filename, filename);
            fm->file = NULL;
            fm->is_open = 0;
        }
    }
    return fm;
}

int file_manager_open_read(FileManager* fm) {
    if (fm && fm->filename && !fm->is_open) {
        fm->file = fopen(fm->filename, "r");
        if (fm->file) {
            fm->is_open = 1;
            return 1;
        }
    }
    return 0;
}

int file_manager_open_write(FileManager* fm) {
    if (fm && fm->filename && !fm->is_open) {
        fm->file = fopen(fm->filename, "w");
        if (fm->file) {
            fm->is_open = 1;
            return 1;
        }
    }
    return 0;
}

int file_manager_read_line(FileManager* fm, char* buffer, int size) {
    if (fm && fm->file && fm->is_open && buffer && size > 0) {
        if (fgets(buffer, size, fm->file)) {
            return 1;
        }
    }
    return 0;
}

int file_manager_write_line(FileManager* fm, const char* line) {
    if (fm && fm->file && fm->is_open && line) {
        if (fputs(line, fm->file) >= 0) {
            return 1;
        }
    }
    return 0;
}

long file_manager_get_size(FileManager* fm) {
    if (fm && fm->file && fm->is_open) {
        long current = ftell(fm->file);
        fseek(fm->file, 0, SEEK_END);
        long size = ftell(fm->file);
        fseek(fm->file, current, SEEK_SET);
        return size;
    }
    return -1;
}

void file_manager_close(FileManager* fm) {
    if (fm && fm->file && fm->is_open) {
        fclose(fm->file);
        fm->file = NULL;
        fm->is_open = 0;
    }
}

int file_manager_is_open(FileManager* fm) {
    if (fm) {
        return fm->is_open;
    }
    return 0;
}

void file_manager_destroy(FileManager* fm) {
    if (fm) {
        if (fm->is_open) {
            file_manager_close(fm);
        }
        if (fm->filename) {
            free(fm->filename);
        }
        free(fm);
    }
}

