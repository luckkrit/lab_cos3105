#include <stdio.h>
#include <stdlib.h>

int main() {
    char *name = getenv("NAME");
    if (name != NULL) {
        printf("NAME = %s\n", name);
    } else {
        printf("NAME is not set\n");
    }
    return 0;
}