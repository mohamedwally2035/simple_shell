/**
 * @file command_processing.c
 * @brief Command processing functions.
 */

#include "shell.h"

/**
 * @brief Checks if the current character in the buffer is a chain delimiter.
 *
 * @param info The parameter struct.
 * @param buf The character buffer.
 * @param p The address of the current position in buf.
 * @return 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[j] == ';') /* found end of this command */
    {
        buf[j] = 0; /* replace semicolon with null */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return 0;
    }

    *p = j;
    return 1;
}

/**
 * @brief Checks if chaining should continue based on the last status.
 *
 * @param info The parameter struct.
 * @param buf The character buffer.
 * @param p The address of the current position in buf.
 * @param i Starting position in buf.
 * @param len Length of buf.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    else if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * @brief Replaces aliases in the tokenized string.
 *
 * @param info The parameter struct.
 * @return 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
    int i;
    list_t *node;
    char *value;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return 0;

        free(info->argv[0]);
        value = _strchr(node->str, '=');
        if (!value)
            return 0;

        value = _strdup(value + 1);
        if (!value)
            return 0;

        info->argv[0] = value;
    }

    return 1;
}

/**
 * @brief Replaces variables in the tokenized string.
 *
 * @param info The parameter struct.
 * @return 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
    int i;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
        }
        else if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
        }
        else
        {
            node = node_starts_with(info->env, &info->argv[i][1], '=');
            if (node)
            {
                replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
            }
            else
            {
                replace_string(&info->argv[i], _strdup(""));
            }
        }
    }

    return 0;
}

/**
 * @brief Replaces a string.
 *
 * @param old The address of the old string.
 * @param new The new string.
 * @return 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}

