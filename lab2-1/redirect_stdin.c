#include <stdio.h>

int main() {
    char line[256];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        printf("Read: %s", line);
    }
    return 0;
}