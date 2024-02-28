#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
    // Initialize the info structure with default values
    info_t info[] = {INFO_INIT};

    int fd = 2; // Default file descriptor

    // Use inline assembly to perform arithmetic on fd
    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    // If a command-line argument is provided, try to open the file
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);

        // Handle errors in opening the file
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }

            return EXIT_FAILURE;
        }

        // Set the read file descriptor in the info structure
        info->readfd = fd;
    }

    // Populate the environment list
    populate_env_list(info);

    // Read command history
    read_history(info);

    // Call the shell function with info structure and arguments
    hsh(info, argv);

    return EXIT_SUCCESS;
}

