#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef double stack_elem;

struct stack
{
    double * data;
    int size;
    int capacity;
};

int stack_constructor(stack * stk, int capacity) {
    stk->data = (stack_elem *)calloc(capacity, sizeof(stack_elem));

    if (stk->data == NULL)
    {
        printf("error of working calloc");
        return 0;
    }

    stk->size = 0;
    stk->capacity = capacity;
    return 0;
}

int stack_destructor(stack*stk) {  // исправить, попортить данные
    free(stk->data);
    return 0;
}

int stack_push(stack*stk, stack_elem value) {
    if (stk->size >= capacity) // выход за границы стека
        exit(STACK_OVERFLOW);

    stk->data[stk->size] = value;
    (stk->size)++;
    return 0;
}

int stack_pop(stack*stk) {
    if (stack->size == 0)  // выход за границы стека
    {
        exit(STACK_UNDERFLOW);
    }

    stack->size--;
    return 0;
}

int stack_dump(stack*stk) {
    for (int i = 0; i < stk->size, ++i) {
        printf("%d ", stk->data[i]);
    }
    printf("\n%d - capacity\n%d - size\n%p - pointer on data", stk->capacity, stk->size, stk->data);
    return 0;
}

