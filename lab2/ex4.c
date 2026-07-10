#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

int main() {
    char buffer[100];
    char ch;
    long fd;
    long bytes;
    int pos = 0;
    int line_num = 1;

    fd = syscall(SYS_open, "lines.txt", O_RDONLY);

    if (fd < 0) {
        syscall(SYS_write, 2, "Error opening file\n", 19);
        return 1;
    }

    // Read character by character
    while ((bytes = syscall(SYS_read, fd, &ch, 1)) > 0) {
        if (ch == '\n') {
            // Display line number
            char num_str[10];
            int n = line_num;
            int digit_pos = 0;

            if (n == 0) {
                num_str[digit_pos++] = '0';
            } else {
                char digits[10];
                int dc = 0;
                while (n > 0) {
                    digits[dc++] = '0' + (n % 10);
                    n /= 10;
                }
                for (int i = dc - 1; i >= 0; i--) {
                    num_str[digit_pos++] = digits[i];
                }
            }
            num_str[digit_pos++] = ':';
            num_str[digit_pos++] = ' ';

            syscall(SYS_write, 1, num_str, digit_pos);
            syscall(SYS_write, 1, buffer, pos);
            syscall(SYS_write, 1, "\n", 1);

            pos = 0;
            line_num++;
        } else {
            buffer[pos++] = ch;
        }
    }

    // Last line (if no newline at end)
    if (pos > 0) {
        syscall(SYS_write, 1, buffer, pos);
        syscall(SYS_write, 1, "\n", 1);
    }

    syscall(SYS_close, fd);

    return 0;
}