#include "shell.h"

/**
 * _strncpy - Copies at most `n` characters from the source string (`src`)
 *   to the destination string (`dest`), ensuring null termination.
 *
 * @dest: The destination string to copy to.
 * @src: The source string to copy from.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strncpy(char *dest, char *src, int n) {
    int i = 0;

    // Copy characters from the source to the destination, up to n-1 characters
    while (src[i] != '\0' && i < n - 1) {
        dest[i] = src[i];
        i++;
    }

    // If the source string is shorter than n, null-terminate the remaining
    // characters in the destination string.
    if (i < n) {
        for (int j = i; j < n; j++) {
            dest[j] = '\0';
        }
    } else {
        // If the source string is longer or equal to n, ensure the destination
        // is still null-terminated.
        dest[i] = '\0';
    }

    return dest;
}

/**
 * _strncat - Appends at most `n` characters from the source string (`src`)
 *   to the end of the destination string (`dest`), ensuring null termination.
 *
 * @dest: The destination string to append to.
 * @src: The source string to append from.
 * @n: The maximum number of characters to append.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strncat(char *dest, char *src, int n) {
    int dest_len = 0, i = 0, j = 0;

    // Find the length of the destination string.
    while (dest[dest_len] != '\0') {
        dest_len++;
    }

    // Append characters from the source to the end of the destination, up to
    // n characters or until the source string ends.
    while (src[j] != '\0' && j < n) {
        dest[dest_len + j] = src[j];
        j++;
    }

    // Null-terminate the combined string if necessary.
    if (j < n) {
        dest[dest_len + j] = '\0';
    }

    return dest;
}

/**
 * _strchr - Locates the first occurrence of a character (`c`) in the string
 *   (`s`) or NULL if the character is not found.
 *
 * @s: The string to search in.
 * @c: The character to search for.
 *
 * Return: A pointer to the first occurrence of the character (`c`) in the
 *         string (`s`) or NULL if not found.
 */
char *_strchr(char *s, char c) {
    while (*s != '\0') {
        if (*s == c) {
            return s;
        }
        s++;
    }

    return NULL;
}
