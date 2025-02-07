#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef double stack_elem;   //FIXME - Просмотреть, где можно заменить типы данных на size_t

struct stack
{
    stack_elem* data;
    size_t size;
    size_t capacity;
};

const stack_elem CANARY = (stack_elem)0xBADC0FFEE;

const stack_elem POISON = (stack_elem)0xBAD1ABA;

enum errorcode
{
    STK_OK =                        0,  // все оки
    STK_OUT_MEMORY =                1,  // calloc не дал память
    STK_NULL_POINTER =              2,  // date = 0
    STK_BAD_SIZE =                  3,  // size < 0
    STK_BAD_CAPACITY =              4,  // capacity <= 0
    STK_SIZE_LARGER_CAPACITY =      5,  // вышли за размер стэка
    // REALLOCK_FAIL =                 6;  // не получить расширить стэк
    BAD_CANARY_1 =                  7,  // левая канарейка
    BAD_CANARY_2 =                  8,  // правая канарейка
};

int verificator(struct stack *stk) // NOTE чек
{
    int error = 0;

    if (stk == NULL)
        error = STK_NULL_POINTER;

    if (stk->data == NULL)
        error = STK_OUT_MEMORY;

    if (stk->size < 0)
        error = STK_BAD_SIZE;

    if (stk->capacity <= 0)
        error = STK_BAD_CAPACITY;

    if (stk->size > stk->capacity)
        error = STK_SIZE_LARGER_CAPACITY;

    if (stk->data[0] != CANARY)
        error = BAD_CANARY_1;

    if (stk->data[stk->capacity + 1] != CANARY)
        error = BAD_CANARY_2;

    return error;
}

const char* decoder(int error) { //NOTE чек
    switch(error) {
        case(STK_OUT_MEMORY):
            return "memory allocation error\n";
        case(STK_NULL_POINTER):
            return "stack pointer is null\n";
        case(STK_BAD_SIZE):
            return "stack size < 0\n";
        case(STK_BAD_CAPACITY):
            return "stack capacity <= 0\n";
        case(STK_SIZE_LARGER_CAPACITY):
            return "size > capacity\n";
        case(BAD_CANARY_1):
            return "canary1 was changed\n";
        case(BAD_CANARY_2):
            return "canary2 was changed\n";
        default:
            return "unknown error\n";
    }
}

int stack_dump(struct stack *stk) { //NOTE чек
    for (size_t i = 1; i < (stk->size) + 1; ++i) {
        printf("%lg ", stk->data[i]);
    }
    printf("\n"
           "%lu - capacity\n"
           "%lu - size\n"
           "%p - pointer on data\n",
           stk->capacity, stk->size, stk->data);
    return 0;
}

int stk_assert(struct stack *stk) { //NOTE чек
    int error = verificator(stk);
    if (error) {
        printf("%s", decoder(error));
        stack_dump(stk);
        assert(0);
    }
    return 0;
}


int stk_null_check(struct stack *stk) { //NOTE чек
    if (stk == NULL) {
        printf("stk pointer is NULL\n");
        assert(0);
    }
    return 0;
}

int put_canary(struct stack *stk)//NOTE чек
{
    stk_null_check(stk);
    stk->data[0] = CANARY;
    stk->data[stk->capacity + 1] = CANARY;

    return 0;
}


int stack_destructor(struct stack* stk) {//NOTE чек
    stk_null_check(stk);
    for (size_t i = 0; i < stk->capacity + 1; ++i)
        stk->data[i] = POISON;
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;

    return 0;
}


int stack_constructor(struct stack * stk, size_t capacity) {

    stk_null_check(stk);

    if (capacity <= 0) {
        printf("capacity is not positive\n");
        assert(0);
    }

    stk->data = (stack_elem *)calloc(capacity + 2, sizeof(stack_elem));
    if (&stk == NULL) {
        printf("memory allocation error\n");
        assert(0);
    }

    stk->size = 0;
    stk->capacity = capacity;
    put_canary(stk);
    stk_assert(stk);

    return 0;
}


int stack_push(struct stack*stk, stack_elem value) {  // добавить с реалоком
    stk_assert(stk);
    if (stk->size  == stk->capacity) {
        printf("size bigger than capacity\n");
        assert(0);
    }

    stk->data[stk->size + 1] = value;
    (stk->size)++;
    stk_assert(stk);

    return 0;
}


int stack_pop(struct stack *stk, stack_elem *pop_elem) { // добавить реаллок вниз
    stk_assert(stk);
    if (stk->size  == 0) {
        printf("empty stack\n");
        assert(0);
    }
    stk->size--;
    *pop_elem = stk->data[stk->size + 1];
    stk->data[stk->size + 1] = POISON;
    stk_assert(stk);

    return 0;
}

int main() {
    struct stack stk = {NULL, 0, 0};
    stack_elem pop_elem = 0;
    stack_constructor(&stk, -20);
    for (int i = 0; i < 21; i++)
    {
        stack_push(&stk, (i + 1) * 10);
    }
    stack_dump(&stk);
    stack_destructor(&stk);
    return 0;
}

