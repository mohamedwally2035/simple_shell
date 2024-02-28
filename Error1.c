#include "shell.h"

// Converts a string to an integer, handling potential errors and overflow
int _erratoi(char *s) {
    // Skip an optional plus sign
    if (*s == '+') {
        s++;
    }

    unsigned long int result = 0;

    // Iterate through the characters, checking for digits
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            result = result * 10 + (s[i] - '0');
            if (result > INT_MAX) { // Handle overflow
                return -1;
            }
        } else {
            // Non-digit found, return error
            return -1;
        }
    }

    return (int)result; // Cast to int before returning
}

// Prints a detailed error message, combining information from various sources
void print_error(info_t *info, char *estr) {
    _eputs(info->fname); // Print filename
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO); // Print line number
    _eputs(": ");
    _eputs(info->argv[0]); // Print command name
    _eputs(": ");
    _eputs(estr); // Print specific error message
}

// Prints a decimal integer to a specified file descriptor
int print_d(int input, int fd) {
    int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
    int count = 0;
    unsigned int abs_value = (input < 0) ? -input : input;

    // Print negative sign if needed
    if (input < 0) {
        __putchar('-');
        count++;
    }

    // Efficiently print digits using a loop and repeated division
    for (unsigned int i = 1000000000; i > 0; i /= 10) {
        if (abs_value / i) {
            __putchar('0' + (abs_value / i));
            count++;
        }
        abs_value %= i;
    }

    // Print the final digit
    __putchar('0' + abs_value);
    count++;

    return count;
}

// Converts a number to a string in a specified base, offering formatting options
char *convert_number(long int num, int base, int flags) {
    static char buffer[50];
    char *ptr = &buffer[49];
    *ptr = '\0';  // Initialize buffer with a null terminator

    unsigned long n = (num >= 0 || (flags & CONVERT_UNSIGNED)) ? num : -num;
    char sign = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? '-' : 0;

    // Use lowercase or uppercase digits based on flags
    const char *digits = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";

    // Build the string in reverse order
    do {
        *--ptr = digits[n % base];
        n /= base;
    } while (n != 0);

    // Prepend the sign if applicable
    if (sign) {
        *--ptr = sign;
    }

    return ptr;
}

// Removes any comments from a string by replacing the first non-escaped '#' with '\0'
void remove_comments(char *buf) {
    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) {
            buf[i] = '\0';
            break;
        }
    }
}
