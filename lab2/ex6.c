#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

int main() {
    long fd;

    fd = syscall(SYS_open, "lines.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        syscall(SYS_write, 2, "Cannot create file\n", 19);
        return 1;
    }

    // Write multiple lines
    syscall(SYS_write, fd, "Line 1\n", 7);
    syscall(SYS_write, fd, "Line 2\n", 7);
    syscall(SYS_write, fd, "Line 3\n", 7);

    syscall(SYS_close, fd);

    syscall(SYS_write, 1, "Three lines written\n", 20);

    return 0;
}