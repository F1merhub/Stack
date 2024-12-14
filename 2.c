#include <stdio.h>

int stack_constructor(struct stack * stk, int capacity) {

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
    stack_assert(&stk);

    return 0;
}



int main() {
    int n = (1<<0);
    int a = (2<<0);
    printf("%d\n%d", n, a);
}
