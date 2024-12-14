#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef double stack_elem;

struct stack
{
    stack_elem* data;
    int size;
    int capacity;
};

int stack_destructor(struct stack* stk) {  // исправить, попортить данные
    free(stk->data);
    stk->data = NULL;
    return 0;
}

int stack_constructor(struct stack * stk, int capacity) {
    stk->data = (stack_elem *)calloc(capacity, sizeof(stack_elem));

    if (stk->data == NULL)
    {
        printf("error of working calloc");
        return -1;
    }

    stk->size = 0;
    stk->capacity = capacity;
    return 0;
}

int stack_push(struct stack*stk, stack_elem value) {
    if (stk->size >= stk->capacity)
        exit(-1);

    stk->data[stk->size] = value;
    (stk->size)++;
    return 0;
}

int stack_pop(struct stack*stk) {
    if (stk->size == 0)
    {
        exit(-1);
    }

    stk->size--;
    return stk->data[stk->size];
}

int stack_dump(struct stack*stk) {
    for (int i = 0; i < stk->size; ++i) {
        printf("%d ", stk->data[i]);
    }
    printf("\n"
           "%d - capacity\n"
           "%d - size\n"
           "%p - pointer on data\n",
           stk->capacity, stk->size, stk->data);
    return 0;
}

int verificator(struct stack * stk) {  // добавить канарейку
    if (stk == NULL)
        return -1;
    if (stk->data == NULL)
        return -1;
    if ((stk->size >= stk->capacity) || (stk->size <= 0))
        return -1;
}

int main() {
    struct stack stk;
    stack_constructor(&stk, 6);
    verificator(&stk);
    for (int i = 0; i < 6; ++i)
        printf("%lg", stk.data[i]);
    return 0;
}
