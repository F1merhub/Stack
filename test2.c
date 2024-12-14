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

const stack_elem POISON = (stack_elem)0xBAD1ABA;


int put_canary(struct stack *stk)
{
    stk->data[0] = CANARY;
    stk->data[stk->capacity + 1] = CANARY;

    return 0;
}

int stack_destructor(struct stack* stk) {  // исправить, попортить данные
    free(stk->data);                       // сделать проверки
    stk->data = NULL;

    return 0;
}

int stack_constructor(struct stack * stk, int capacity) {  // сделать нормальную проверку
    stk->data = (stack_elem *)calloc(capacity + 2, sizeof(stack_elem));

    if (stk->data == NULL)
    {
        printf("memory allocation error\n");
        return -1; // добавить название
    }

    stk->size = 0;
    stk->capacity = capacity;
    put_canary(stk);

    return 0;
}

int stack_push(struct stack*stk, stack_elem value) {
    assert(stk->size < stk->capacity);  // сделать проверки
    stk->data[stk->size + 1] = value;
    (stk->size)++;
    return 0;
}

int stack_pop(struct stack*stk, stack_elem *pop_elem) { // возратить элемент
    assert(stk->size > 0);  // нормальная проверка
    stk->size--;
    *pop_elem = stk->data[stk->size + 1];
    stk->data[stk->size + 1] = POISON;
    return 0;
}

int stack_dump(struct stack*stk) {
    for (int i = 1; i < (stk->size) + 1; ++i) {
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
    struct stack stk = {NULL, 0, 0};
    stack_elem pop_elem = 0;
    stack_constructor(&stk, 6);
    stack_push(&stk, 6);
    stack_push(&stk, 6);
    stack_push(&stk, 6);
    stack_push(&stk, 6);
    stack_push(&stk, 6);
    stack_push(&stk, 6);
    stack_pop(&stk, &pop_elem);
    // printf("%lg", stk.data[1]);
    // verificator(&stk);
    stack_dump(&stk);
    stack_destructor(stk)
    return 0;
}


