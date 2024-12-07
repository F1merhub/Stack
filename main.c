#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef double stack_elem;

struct stack
{
    stack_elem * data;
    int size;
    int capacity;
};

int main() {
    struct stack stk;
    int capacity = 0;
    scanf("%d", &capacity);



    return 0;
}
