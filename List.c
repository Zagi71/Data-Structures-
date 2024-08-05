#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include <assert.h>

List newList(void) {
    // Your implementation of newList()
    List list = malloc(sizeof(ListObj));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->cursor = NULL;
    list->length = 0;
    list->index_cursor = -1;
    return list;
}

void freeList(List *pL) {
    // Your implementation of freeList()
    if (pL == NULL || *pL == NULL) {
        return;
    }
    NodePtr curr = (*pL)->head;
    while (curr != NULL) {
        NodePtr temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(*pL);
    *pL = NULL;
}

int length(List L) {
    // Your implementation of length()
    if (L == NULL) {
        return -1;
    }
    return L->length;
}

int index(List L) {
    // Your implementation of indexC()
    if (L == NULL) {
        return -1;
    }
    return L->index_cursor;
}

int front(List L) {
    // Your implementation of front()
    if (L == NULL || L->head == NULL) {
        return -1;
    }
    return L->head->data;
}

int back(List L) {
    // Your implementation of back()
    if (L == NULL || L->head == NULL) {
        return -1;
    }
    // return tail
    return L->tail->data;
}

int get(List L) {
    // Your implementation of get()
    if (L == NULL || L->head == NULL || L->index_cursor == -1 || L->length == 0 || L->cursor == NULL) {
        return -1;
    }
    return L->cursor->data;
}

bool equals(List A, List B) {
    // Your implementation of equals()
    if (A == NULL || B == NULL) {
        return false;
    }
    if (A->length != B->length) {
        return false;
    }
    NodePtr currA = A->head;
    NodePtr currB = B->head;
    while (currA != NULL && currB != NULL) {
        if (currA->data != currB->data) {
            return false;
        }
        currA = currA->next;
        currB = currB->next;
    }
    return true;
}


// Manipulation procedures ----------------------------------------------------

void clear(List L) {
    // Your implementation of clear()
    if (L == NULL) {
        return;
    }
    NodePtr curr = L->head;
    while (curr != NULL) {
        NodePtr temp = curr;
        curr = curr->next;
        free(temp);
    }
    L->head = NULL;
    L->tail = NULL;
    L->cursor = NULL;
    L->index_cursor = -1;
    L->length = 0;
}

void set(List L, int x) {
    // Your implementation of set()
    if (L == NULL || L->head == NULL || L->index_cursor == -1 || L->length == 0 || L->cursor == NULL) {
        return;
    }
    L->cursor->data = x;
}

void moveFront(List L) {
    // Your implementation of moveFront()
    if (L == NULL || L->head == NULL) {
        return;
    }
    L->cursor = L->head;
    L->index_cursor = 0;
}

void moveBack(List L) {
    // Your implementation of moveBack()
    if (L == NULL || L->head == NULL) {
        return;
    }
    L->cursor = L->tail;
    L->index_cursor = L->length - 1;
}

void movePrev(List L) {
    // Your implementation of movePrev()
    if (L == NULL || L->head == NULL || L->index_cursor == -1) {
        return;
    }
    if (L->cursor == L->head) {
        L->cursor = NULL;
        L->index_cursor = -1;
    } else {
        L->cursor = L->cursor->prev;
        L->index_cursor--;
    }
}

void moveNext(List L) {
    // Your implementation of moveNext()
    if (L == NULL || L->head == NULL || L->index_cursor == -1) {
        return;
    }
    if (L->cursor == L->tail) {
        L->cursor = NULL;
        L->index_cursor = -1;
    } else {
        L->cursor = L->cursor->next;
        L->index_cursor++;
    }
}

void prepend(List L, int x) {
    // Your implementation of prepend()

    NodePtr node = malloc(sizeof(NodeObj));
    if (node == NULL) {
        return;
    }
    node->data = x;
    node->next = L->head;
    node->prev = NULL;
    if (L->head != NULL) {
        L->head->prev = node;
    }
    L->head = node;
    if (L->tail == NULL) {
        L->tail = node;
    }
    L->length++;
    if (L->index_cursor != -1) {
        L->index_cursor++;
    }
}

void append(List L, int x) {
    // Your implementation of append()        
    
    NodePtr node = malloc(sizeof(NodeObj));


    node->data = x;
    node->next = NULL;
    node->prev = L->tail;
   
    if (L->head == NULL) {
        L->head = node;
      
    }
    else if (L->tail != NULL) {
        L->tail->next = node;
    }
    L->tail = node;
    L->length++;
}

void insertBefore(List L, int x) {
    // Your implementation of insertBefore()
    if (L == NULL || L->head == NULL || L->index_cursor == -1) {
        return;
    }
    if (L->cursor == L->head) {
        prepend(L, x);
    } else {
        NodePtr node = malloc(sizeof(NodeObj));
        node->data = x;
        node->next = L->cursor;
        node->prev = L->cursor->prev;
        L->cursor->prev->next = node;
        L->cursor->prev = node;
        L->length++;
        L->index_cursor++;
    }
}

void insertAfter(List L, int x) {
    // Your implementation of insertAfter()
    if (L == NULL || L->head == NULL || L->index_cursor == -1) {
        return;
    }
    if (L->cursor == L->tail) {
        append(L, x);
    } else {
        NodePtr node = malloc(sizeof(NodeObj));
        node->data = x;
        node->next = L->cursor->next;
        node->prev = L->cursor;
        L->cursor->next->prev = node;
        L->cursor->next = node;
        L->length++;
    }
}

void deleteFront(List L) {
    // Your implementation of deleteFront()
    if (L == NULL || L->head == NULL) {
        return;
    }
    if (L->cursor == L->head) {
        L->cursor = NULL;
        L->index_cursor = -1;
    }
    NodePtr temp = L->head;
    L->head = L->head->next;
    if (L->head != NULL) {
        L->head->prev = NULL;
    }
    free(temp);
    L->length--;
    if (L->index_cursor != -1) {
        L->index_cursor--;
    }
}

void deleteBack(List L) {
    // Your implementation of deleteBack()
    if (L == NULL || L->head == NULL) {
        return;
    }
    if (L->cursor == L->tail) {
        L->cursor = NULL;
        L->index_cursor = -1;
    }
    NodePtr temp = L->tail;
    L->tail = L->tail->prev;
    if (L->tail != NULL) {
        L->tail->next = NULL;
    }
    free(temp);
    L->length--;
}

void delete(List L) {
    // Your implementation of delete()
    if (L == NULL || L->head == NULL || L->index_cursor == -1) {
        return;
    }
    if (L->cursor == L->head) {
        deleteFront(L);
    } else if (L->cursor == L->tail) {
        deleteBack(L);
    } else {
        NodePtr temp = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        L->cursor = NULL;
        L->index_cursor = -1;
        free(temp);
        L->length--;
    }
}

// Other operations -----------------------------------------------------------

void printList(FILE *out, List L) {
    // Your implementation of printList()
    if (L == NULL || L->head == NULL) {
        return;
    }
    NodePtr curr = L->head;
    while (curr != NULL) {
        fprintf(out, "%d ", curr->data);
        curr = curr->next;
    }
}

List copyList(List L) {
    // Your implementation of copyList()
    if (L == NULL || L->head == NULL) {
        return NULL;
    }
    List list = newList();
    NodePtr curr = L->head;
    while (curr != NULL) {
        append(list, curr->data);
        curr = curr->next;
    }
    return list;
}

List concatList(List A, List B) {
    // Your implementation of concatList()
    if (A == NULL || A->head == NULL || B == NULL || B->head == NULL) {
        return NULL;
    }
    List list = newList();
    NodePtr curr = A->head;
    while (curr != NULL) {
        append(list, curr->data);
        curr = curr->next;
    }
    curr = B->head;
    while (curr != NULL) {
        append(list, curr->data);
        curr = curr->next;
    }
    return list;
}
