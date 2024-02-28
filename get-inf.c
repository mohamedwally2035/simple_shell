#include "shell.h"

// Initialize specific fields of the info_t structure to empty values
void reset_info_fields(info_t *info) {
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

// Set up the info_t struct with initial data
void initialize_info(info_t *info, char **av) {
    info->fname = av[0];

    if (info->arg) {
        info->argv = strtow(info->arg, " \t");

        // Handle potential allocation failure
        if (!info->argv) {
            info->argv = allocate_argv_for_single_argument(info->arg);
        }

        info->argc = count_arguments(info->argv);

        apply_aliases(info);
        apply_variable_replacements(info);
    }
}

// Free allocated memory within the info_t struct
void deallocate_info_resources(info_t *info, int all) {
    free(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (all) {
        free_if_not_command_buffer(info->arg);
        free_lists(info);
        free(info->environ);
        info->environ = NULL;
        deallocate_command_buffer(info);
        close_extra_file_descriptors(info);
        flush_output();
    }
}
