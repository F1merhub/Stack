#include "main.h"   // go together

int main() {

    struct stack stk = {NULL, 0, 0};
    stack_elem pop_elem = 0;
    stack_constructor(&stk, 21);
    for (int i = 0; i < 21; i++)
    {
        stack_push(&stk, (i + 1) * 10);
    }
    stack_dump(&stk);
    stack_destructor(&stk);

    return 0;
}

