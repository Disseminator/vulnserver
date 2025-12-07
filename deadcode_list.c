// Dead Code - Linked List Class
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
    int count;
} LinkedList;

LinkedList* linked_list_create() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list) {
        list->head = NULL;
        list->count = 0;
    }
    return list;
}

void linked_list_append(LinkedList* list, int data) {
    if (list) {
        ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
        if (new_node) {
            new_node->data = data;
            new_node->next = NULL;
            
            if (list->head == NULL) {
                list->head = new_node;
            } else {
                ListNode* current = list->head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = new_node;
            }
            list->count++;
        }
    }
}

int linked_list_get(LinkedList* list, int index) {
    if (list && list->head && index >= 0 && index < list->count) {
        ListNode* current = list->head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    return -1;
}

int linked_list_remove(LinkedList* list, int index) {
    if (list && list->head && index >= 0 && index < list->count) {
        ListNode* to_remove;
        if (index == 0) {
            to_remove = list->head;
            list->head = list->head->next;
        } else {
            ListNode* current = list->head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            to_remove = current->next;
            current->next = to_remove->next;
        }
        int data = to_remove->data;
        free(to_remove);
        list->count--;
        return data;
    }
    return -1;
}

int linked_list_size(LinkedList* list) {
    if (list) {
        return list->count;
    }
    return 0;
}

void linked_list_clear(LinkedList* list) {
    if (list) {
        ListNode* current = list->head;
        while (current != NULL) {
            ListNode* next = current->next;
            free(current);
            current = next;
        }
        list->head = NULL;
        list->count = 0;
    }
}

void linked_list_destroy(LinkedList* list) {
    if (list) {
        linked_list_clear(list);
        free(list);
    }
}

