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

int put_canary(stack *stk)
{
    stk->data[0] = CANARY;
    stk->data[stk->capacity + 1] = CANARY;

    return 0;
}

void stk_Null_check(struct stack* stk)
{
    if (stk == NULL)
    {
        DBG_FPRINTF(stderr, COLOR_RED "ERROR: STK POINTER IS NULL\n" COLOR_RESET);
        assert(0);
    }
}
