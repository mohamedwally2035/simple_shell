#include "shell.h"

/**
 * _eputs - Prints a string to standard error (stderr).
 *
 * @str: The string to be printed.
 *
 * Return: Nothing (void).
 */
void _eputs(char *str) {
    if (!str) {
        return;
    }

    // Write the string directly using write(2, ...)
    write(2, str, _strlen(str));
}

/**
 * _eputchar - Writes a character to standard error (stderr).
 *
 * @c: The character to be printed.
 *
 * Return: 1 on success, -1 on error.
 */
int _eputchar(char c) {
    // Write the character directly using write(2, ...)
    return write(2, &c, 1);
}

/**
 * _putfd - Writes a character to a specified file descriptor.
 *
 * @c: The character to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: 1 on success, -1 on error.
 */
int _putfd(char c, int fd) {
    static int i;
    static char buf[WRITE_BUF_SIZE];

    // Use buffering for improved performance
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        ssize_t bytes_written = write(fd, buf, i);
        if (bytes_written == -1) {
            return -1;
        }
        i = 0;
    }
    if (c != BUF_FLUSH) {
        buf[i++] = c;
    }
    return 1;
}

/**
 * _putsfd - Prints a string to a specified file descriptor.
 *
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed on success, -1 on error.
 */
int _putsfd(char *str, int fd) {
    if (!str) {
        return 0;
    }

    // Unbuffered write for simplicity
    ssize_t bytes_written = write(fd, str, _strlen(str));
    if (bytes_written == -1) {
        return -1;
    }
    return bytes_written;
}
