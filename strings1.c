/**
 * @file string_operations.c
 * @brief String manipulation functions.
 */

#include "shell.h"

/**
 * @brief Copies a string.
 *
 * @param dest The destination buffer.
 * @param src The source string.
 * @return Pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == NULL)
        return dest;

    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return dest;
}

/**
 * @brief Duplicates a string.
 *
 * @param str The string to duplicate.
 * @return Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *duplicate;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    duplicate = malloc(sizeof(char) * (length + 1));
    if (!duplicate)
        return NULL;

    for (length++; length--;)
        duplicate[length] = *--str;

    return duplicate;
}

/**
 * @brief Prints a string to stdout.
 *
 * @param str The string to be printed.
 */
void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * @brief Writes a character to stdout.
 *
 * @param c The character to print.
 * @return On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int bufferIndex;
    static char outputBuffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
    {
        write(1, outputBuffer, bufferIndex);
        bufferIndex = 0;
    }

    if (c != BUF_FLUSH)
        outputBuffer[bufferIndex++] = c;

    return 1;
}

