#include "shell.h"

/**
 * get_history_file - Constructs the history file path.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
    char *dir = _getenv(info, "HOME=");
    if (!dir)
        return NULL;

    char *filename = malloc(_strlen(dir) + _strlen(HIST_FILE) + 2);
    if (!filename)
    {
        free(dir);
        return NULL;
    }

    _strcpy(filename, dir);
    _strcat(filename, "/");
    _strcat(filename, HIST_FILE);

    free(dir);
    return filename;
}

/**
 * write_history - Writes the command history to a file.
 * @info: Parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return -1;

    int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    list_t *node = info->history;
    while (node)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
        node = node->next;
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

/**
 * read_history - Reads command history from a file.
 * @info: Parameter struct.
 *
 * Return: Number of commands read on success, 0 on failure.
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;

    int fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    struct stat st;
    if (fstat(fd, &st) < 0 || st.st_size < 2)
    {
        close(fd);
        return 0;
    }

    char *buf = malloc(st.st_size + 1);
    if (!buf)
    {
        close(fd);
        return 0;
    }

    ssize_t rdlen = read(fd, buf, st.st_size);
    close(fd);

    if (rdlen <= 0)
    {
        free(buf);
        return 0;
    }

    buf[st.st_size] = '\0';

    int last = 0, linecount = 0;
    for (int i = 0; i < st.st_size; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != st.st_size)
        build_history_list(info, buf + last, linecount++);

    free(buf);

    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);

    return info->histcount;
}

/**
 * build_history_list - Adds an entry to the history linked list.
 * @info: Parameter struct.
 * @buf: Buffer containing the command.
 * @linecount: The history line count.
 *
 * Return: 0 on success, -1 on failure.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = info->history;

    if (info->history)
        node = info->history;

    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}

