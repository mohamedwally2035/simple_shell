#include "shell.h"

/**
 * _myhistory - Displays the history list, one command per line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
    // Call print_list function to display the command history
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - Removes an alias.
 * @info: Parameter struct.
 * @str: The string representing the alias.
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    // Find the position of '=' in the alias string
    p = _strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    // Delete the alias by its name
    ret = delete_node_at_index(&(info->alias),
                               get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The string representing the alias.
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    // Find the position of '=' in the alias string
    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(info, str));

    // Unset any existing alias with the same name
    unset_alias(info, str);
    // Add the new alias to the list
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        // Find the position of '=' in the alias string
        p = _strchr(node->str, '=');
        // Print the alias name
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        // Print the alias value
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - Mimics the alias built-in (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    // If no arguments provided, print all aliases
    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }

    // Loop through provided arguments
    for (i = 1; info->argv[i]; i++)
    {
        // If argument contains '=', set alias
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        // If no '=', print alias with matching name
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

