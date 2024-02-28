#include "shell.h"

/**
 * is_executable_file - Checks if a file is an executable command.
 * @path: Path to the file.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */
int is_executable_file(char *path)
{
    struct stat st;

    if (!path || stat(path, &st) != 0)
        return 0;

    return (st.st_mode & S_IFREG) ? 1 : 0;
}

/**
 * extract_substring - Extracts a substring from a string based on start and stop indices.
 * @source: The source string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Dynamically allocated buffer containing the extracted substring.
 */
char *extract_substring(char *source, int start, int stop)
{
    char *buffer = malloc(stop - start + 1);
    if (!buffer)
        return NULL;

    int k = 0;
    for (int i = start; i < stop; i++)
    {
        if (source[i] != ':')
            buffer[k++] = source[i];
    }

    buffer[k] = '\0';
    return buffer;
}

/**
 * find_command_in_path - Finds the full path of a command in the PATH string.
 * @info: The info struct.
 * @path_str: The PATH string.
 * @command: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_command_in_path(info_t *info, char *path_str, char *command)
{
    if (!path_str)
        return NULL;

    if (_strlen(command) > 2 && starts_with(command, "./"))
    {
        if (is_executable_file(command))
            return command;
    }

    int i = 0, curr_pos = 0;
    char *full_path;

    while (1)
    {
        if (!path_str[i] || path_str[i] == ':')
        {
            full_path = extract_substring(path_str, curr_pos, i);
            if (!*full_path)
                _strcat(full_path, command);
            else
            {
                _strcat(full_path, "/");
                _strcat(full_path, command);
            }

            if (is_executable_file(full_path))
                return full_path;

            if (!path_str[i])
                break;

            curr_pos = i;
        }

        i++;
    }

    return NULL;
}

