#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum errorcode
{
A = 5,
B = 1,
C = 0,
};


int main() {
    // if (1 && B)
    //     printf("YES");
    // else
    //     printf("NO");
    int k;
    k = B;
    char m[5] = "aa";
    printf("%c", m[k]);
    return 0;
}
