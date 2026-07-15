#include <unistd.h>
#include <sys/syscall.h>

int main() {
    char buffer[50];
    long bytes;

    // Display prompt
    char *prompt = "Enter your name: ";
    syscall(SYS_write, 1, prompt, 17);

    // Read input
    bytes = syscall(SYS_read, 0, buffer, 50);

    // Display greeting
    char *greeting = "Hello, ";
    syscall(SYS_write, 1, greeting, 7);

    // Echo name
    syscall(SYS_write, 1, buffer, bytes);

    return 0;
}