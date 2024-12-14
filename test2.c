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

enum errorcode
{
    STK_OK =                        0;  // нормки
    STK_OUT_MEMORY =                1;  // calloc не дал память
    STK_REALLOC_FAILED =            2;
    STK_EMPTY_STACK =               3;
    SIZE_LARGER_CAPACITY =          4;  // вышли за размер стэка
    STK_CAPACITY_NOT_EXSIST =       5;
    BAD_CAPACITY =                  6;
    BAD_SIZE =                      7;
    STK_NULL_POINTER =              8;  // date = 0
    CANT_REALLOC_TO_FREE =          10;
    BAD_CANARY_1 =                  11;
    BAD_CANARY_2 =                  12;
};

int verificator(stack *stk)
{
    int error = 0;
    stk_null_check(stk);

    if (stk->data == NULL)
        error = error | STK_OUT_MEMORY;
    else
    {
        if (stk->data[0] != CANARY)
            error = error | BAD_CANARY_1;
        if (stk->data[stk->capacity + 1] != CANARY)
            error = error | BAD_CANARY_2;
    }

    if ((size_t)stk->size > stk->capacity)
        error = error | STK_SIZE_LARGER_CAPACITY;

    if (stk->size < 0)
        error = error | BAD_SIZE;

    if (stk->capacity == 0)
        error = error | STK_CAPACITY_NOT_EXSIST;

    return error;
}



int stk_null_check(struct stack *stk) {  // много раз встречается
    if (stk == NULL) {
        printf("stk pointer is NULL");
        assert(0);
    }
    return 0;
}

int put_canary(struct stack *stk)
{
    stk->data[0] = CANARY;
    stk->data[stk->capacity + 1] = CANARY;

    return 0;
}


int stack_destructor(struct stack* stk) {
    stk_null_check(stk);
    for (int i = 0; i < capacity + 1; ++i)
        stk->data[i] = POISON;
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;

    return 0;
}


int stack_constructor(struct stack * stk, int capacity) {

    stk_null_check(stk);

    if (capacity <= 0) {
        printf("capacity is not positive");
        assert(0);
    }

    stk->data = (stack_elem *)calloc(capacity + 2, sizeof(stack_elem));
    if (&stk == NULL) {
        printf("memory allocation error");
        assert(0);
    }

    stk->size = 0;
    stk->capacity = capacity;
    put_canary(stk);
    stk_assert(&stk);

    return 0;
}


int stack_push(struct stack*stk, stack_elem value) {  // добавить с реалоком
    stk_assert(stk);
    if (size  == capacity) {
        printf("size bigger than capacity");
        assert(0);
    }

    stk->data[stk->size + 1] = value;
    (stk->size)++;
    stk_asssert(stk);

    return 0;
}


int stack_pop(struct stack*stk, stack_elem *pop_elem) { // добавить реаллок вниз
    stk_assert(stk);
    stk->size--;
    *pop_elem = stk->data[stk->size + 1];
    stk->data[stk->size + 1] = POISON;
    stk_assert(stk);

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
    stack_dump(&stk);
    stack_destructor(stk)
    return 0;
}


