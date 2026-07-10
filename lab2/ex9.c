int main() {
    char *filename = "data.txt";
    char buffer[200];
    long fd, bytes;

    // Open
    asm volatile (
        "syscall"
        : "=a" (fd)
        : "a" (2), "D" (filename), "S" (0)
        : "rcx", "r11"
    );

    // Read
    asm volatile (
        "syscall"
        : "=a" (bytes)
        : "a" (0), "D" (fd), "S" (buffer), "d" (200)
        : "rcx", "r11", "memory"
    );

    // Display
    asm volatile (
        "syscall"
        :
        : "a" (1), "D" (1), "S" (buffer), "d" (bytes)
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