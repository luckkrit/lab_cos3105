int main() {
    char *filename = "test.txt";
    char *message = "Testing 123\n";
    long fd;

    // Open/Create
    asm volatile (
        "syscall"
        : "=a" (fd)
        : "a" (2), "D" (filename), "S" (0101), "d" (0644)
        : "rcx", "r11"
    );

    // Write
    asm volatile (
        "syscall"
        :
        : "a" (1), "D" (fd), "S" (message), "d" (12)
        : "rcx", "r11"
    );

    // Close
    asm volatile (
        "syscall"
        :
        : "a" (3), "D" (fd)
        : "rcx", "r11"
    );

    return 0;
}