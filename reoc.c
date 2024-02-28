#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @dest: Pointer to the memory area.
 * @b: The byte to fill @dest with.
 * @n: The number of bytes to be filled.
 *
 * Return: Pointer to the memory area @dest.
 */
char *_memset(char *dest, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        dest[i] = b;

    return dest;
}

/**
 * free_string_array - Frees an array of strings.
 * @str_array: Array of strings to free.
 */
void free_string_array(char **str_array)
{
    if (!str_array)
        return;

    char **temp = str_array;

    while (*str_array)
        free(*str_array++);

    free(temp);
}

/**
 * _realloc_memory - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block.
 */
void *_realloc_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
        return malloc(new_size);

    if (!new_size)
        return free(ptr), NULL;

    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);

    if (!new_ptr)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;

    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];

    free(ptr);

    return new_ptr;
}

