#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct thing {
    char* name;
    unsigned int x;
} thing_t;

int main() {
    List l = newList();
    thing_t* t  = (thing_t*)malloc(sizeof(thing_t));
    t->name = "Test";
    t->x = 422201;
    append(l, (void*)t);
    moveFront(l);
    thing_t* th = (thing_t*)get(l);
    printf("name = %s, x = %d\n", th->name, th->x);
    free(th);
    freeList(&l);
}
