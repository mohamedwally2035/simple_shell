#include "shell.h"

/**
 * _myenv - Prints the current environment variables.
 *
 * @info: Structure containing potential arguments (unused).
 *
 * Return: Always 0 (success).
 */
int _myenv(info_t *info) {
    size_t i = 0;

    while (environ[i]) {
        _puts(environ[i]);
        _putchar('\n');
        i++;
    }

    return 0;
}

/**
 * _getenv - Retrieves the value of an environment variable.
 *
 * @info: Structure containing potential arguments (unused).
 * @name: The environment variable name to search for.
 *
 * Return: The value of the environment variable if found, NULL otherwise.
 */
char *_getenv(info_t *UNUSED(info), const char *name) {
    size_t i = 0;
    size_t name_len = _strlen(name);

    while (environ[i]) {
        if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            return environ[i] + name_len + 1;  // Return the value after the '=' sign
        }
        i++;
    }

    return NULL;
}

/**
 * _mysetenv - Sets or modifies an environment variable.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int _mysetenv(info_t *info) {
    char *new_env_var = NULL;

    if (info->argc != 3) {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }

    new_env_var = malloc(_strlen(info->argv[1]) + _strlen(info->argv[2]) + 2);
    if (!new_env_var) {
        perror("Malloc failed");
        return 1;
    }

    _strcpy(new_env_var, info->argv[1]);
    _strcat(new_env_var, "=");
    _strcat(new_env_var, info->argv[2]);

    return setenv(info->argv[1], info->argv[2], 1);  // Overwrite if exists
}

/**
 * _myunsetenv - Removes an environment variable.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int _myunsetenv(info_t *info) {
    if (info->argc == 1) {
        _eputs("Too few arguments.\n");
        return 1;
    }

    for (int i = 1; i < info->argc; i++) {
        if (unsetenv(info->argv[i]) != 0) {
            return 1;  // Return failure if any unsetting fails
        }
    }

    return 0;
}

/**
 * populate_env_list - Initializes the environment variable linked list.
 *
 * @info: Structure containing potential arguments (unused).
 *
 * Return: Always 0 (success).
 */
int populate_env_list(info_t *info) {
    list_t *node = NULL;
    size_t i = 0;

    while (environ[i]) {
        add_node_end(&node, environ[i], 0);
        i++;
    }

    info->env = node;
    return 0;
}
