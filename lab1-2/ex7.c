#include <unistd.h>

int main() {
    const char *message = "Hello from inline assembly!\n";
    int len = 29;

    // System call: write(stdout, message, length)
    // syscall number 1 (write) on x86-64
    asm volatile (
        "movq $1, %%rax\n"      // syscall number (write)
        "movq $1, %%rdi\n"      // file descriptor (stdout)
        "movq %0, %%rsi\n"      // buffer address
        "movq %1, %%rdx\n"      // count (length)
        "syscall\n"             // interrupt
        :
        : "r" (message), "r" ((long)len)
        : "rax", "rdi", "rsi", "rdx"
    );

    return 0;
}