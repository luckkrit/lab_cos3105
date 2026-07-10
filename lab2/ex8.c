int main() {
    char buffer[100];
    long bytes_read;

    const char *prompt = "Enter text: ";

    asm volatile (
        "movq $1, %%rax\n"
        "movq $1, %%rdi\n"
        "movq %0, %%rsi\n"
        "movl %1, %%edx\n"      // Use movl for 32-bit immediate
        "syscall\n"
        :
        : "r" (prompt), "i" (12)  // "i" for immediate constant
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11"
    );

    asm volatile (
        "movq $0, %%rax\n"
        "movq $0, %%rdi\n"
        "movq %1, %%rsi\n"
        "movq $100, %%rdx\n"
        "syscall\n"
        "movq %%rax, %0\n"
        : "=r" (bytes_read)
        : "r" (buffer)
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory"
    );

    asm volatile (
        "movq $1, %%rax\n"
        "movq $1, %%rdi\n"
        "movq %0, %%rsi\n"
        "movq %1, %%rdx\n"
        "syscall\n"
        :
        : "r" (buffer), "r" (bytes_read)
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11"
    );

    return 0;
}