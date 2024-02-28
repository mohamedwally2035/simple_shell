#include "shell.h"

/**
 * get_list_length - Determines the length of the linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t get_list_length(const list_t *head)
{
    size_t size = 0;

    while (head)
    {
        head = head->next;
        size++;
    }

    return size;
}

/**
 * list_to_strings - Returns an array of strings from list->str.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
    size_t size = get_list_length(head);
    char **strs = NULL;
    char **current_str = NULL;

    if (!head || size == 0)
        return NULL;

    strs = malloc(sizeof(char *) * (size + 1));
    if (!strs)
        return NULL;

    current_str = strs;

    while (head)
    {
        *current_str = _strdup(head->str ? head->str : "(nil)");
        if (!*current_str)
        {
            for (char **p = strs; p < current_str; ++p)
                free(*p);
            free(strs);
            return NULL;
        }

        ++current_str;
        head = head->next;
    }

    *current_str = NULL;

    return strs;
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *head)
{
    size_t size = 0;

    while (head)
    {
        _puts(convert_number(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        size++;
    }

    return size;
}

/**
 * find_node_with_prefix - Finds a node whose string starts with a prefix.
 * @head: Pointer to the list head.
 * @prefix: Prefix to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matching node or NULL.
 */
list_t *find_node_with_prefix(list_t *head, char *prefix, char c)
{
    char *match = NULL;

    while (head)
    {
        match = starts_with(head->str, prefix);
        if (match && ((c == -1) || (*match == c)))
            return head;

        head = head->next;
    }

    return NULL;
}

/**
 * get_node_index - Gets the index of a node in the list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;

        head = head->next;
        index++;
    }

    return -1;
}

