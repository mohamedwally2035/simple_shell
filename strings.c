/**
 * @file string_utils.c
 * @brief String utility functions.
 */

#include "shell.h"

/**
 * @brief Returns the length of a string.
 *
 * @param str The string whose length to check.
 * @return Integer length of the string.
 */
int _strlen(char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (*str++)
        length++;

    return length;
}

/**
 * @brief Performs lexicographic comparison of two strings.
 *
 * @param str1 The first string.
 * @param str2 The second string.
 * @return Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2.
 */
int _strcmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);

        str1++;
        str2++;
    }

    return (*str1 - *str2);
}

/**
 * @brief Checks if the string starts with a given substring.
 *
 * @param str The string to search.
 * @param prefix The substring to find.
 * @return Address of the next character of str after the prefix, or NULL if not found.
 */
char *starts_with(const char *str, const char *prefix)
{
    while (*prefix)
    {
        if (*prefix++ != *str++)
            return NULL;
    }

    return (char *)str;
}

/**
 * @brief Concatenates two strings.
 *
 * @param dest The destination buffer.
 * @param src The source buffer.
 * @return Pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = *src;

    return result;
}

