// get_environ
char **get_environ(char ***environ, int *env_changed) {
    if (!*environ || *env_changed) {
        *environ = list_to_strings(info->env);
        *env_changed = 0;
    }
    return *environ;
}

// _unsetenv
int _unsetenv(char **env, char *var) {
    list_t *node = *env;
    size_t i = 0;
    char *p;

    if (!node || !var) {
        return 0;
    }

    while (node) {
        p = starts_with(node->str, var);
        if (p && *p == '=') {
            delete_node_at_index(env, i);
            i = 0;
            node = *env;
            continue;
        }
        node = node->next;
        i++;
    }
    return 1; // Return 1 instead of info->env_changed for simplicity
}

// _setenv
int _setenv(char **env, char *var, char *value) {
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value) {
        return 0;
    }

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf) {
        return 1;
    }
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);

    node = *env;
    while (node) {
        p = starts_with(node->str, var);
        if (p && *p == '=') {
            free(node->str);
            node->str = buf;
            return 0;
        }
        node = node->next;
    }

    add_node_end(env, buf, 0);
    free(buf);
    return 0;
}

