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

const stack_elem CANARY = (stack_elem)0xBADC0FFEE;

const stack_elem POISON = (stack_elem)0xBAD1ABA

int put_canary(stack *stk)
{
    stk->data[0] = CANARY;
    stk->data[stk->capacity + 1] = CANARY;

    return 0;
}

int stack_destructor(struct stack* stk) {  // исправить, попортить данные
    free(stk->data);
    stk->data = NULL;

    return 0;
}

int stack_constructor(struct stack * stk, int capacity) {
    stk->data = (stack_elem *)calloc(capacity + 2, sizeof(stack_elem));

    if (stk->data == NULL)
    {
        printf("memory allocation error\n");
        return ; // добавить название
    }

    stk->size = 0;
    stk->capacity = capacity;
    put_canary(stk);

    return 0;
}

int stack_push(struct stack*stk, stack_elem value) {
    assert(stk->size < stk->capacity);  // убрать поставить ретурн
    stk->data[stk->size + 1] = value;
    (stk->size)++;
    return 0;
}

int stack_pop(struct stack*stk) { // возратить элемент
    assert(stk->size > 0);  // убрать поставить ретурн
    stk->size--;
    *elem_from_stack = stk->data[stk->size + 1];
    stk->data[stk->size + 1] = POISON;
}

int stack_dump(struct stack*stk) {
    for (int i = 0; i < stk->size; ++i) {
        printf("%lg ", stk->data[i]);
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
    stack_push(&stk, 3);
    stack_push(&stk, 4);
    stack_push(&stk, 4);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_pop(&stk);
    stack_pop(&stk);
    verificator(&stk);
    stack_dump(&stk);
    return 0;
}


