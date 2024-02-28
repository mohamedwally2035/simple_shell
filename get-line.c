#include "shell.h"

**Function:** `input_buf`

- **Purpose:**
    - Reads input from `stdin` into a buffer, handling potential buffer exhaustion and chaining commands.
- **Parameters:**
    - `info`: Pointer to an `info_t` structure holding shell information.
    - `buf`: Pointer to a char pointer; will be assigned the allocated buffer.
    - `len`: Pointer to a size_t variable; will be assigned the buffer length.
- **Return:**
    - `ssize_t`: Number of bytes read, or -1 on error/EOF.

```c
ssize_t input_buf(info_t *info, char **buf, size_t *len) {
    ssize_t bytes_read = 0;
    size_t buffer_length = 0;

    // Check if the buffer is empty
    if (!*len) {
        // Free any previously allocated buffer and reset pointers
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);

        // Read input using either `getline` or custom `_getline` depending on USE_GETLINE macro
#if USE_GETLINE
        bytes_read = getline(buf, &buffer_length, stdin);
#else
        bytes_read = _getline(info, buf, &buffer_length);
#endif

        // Handle input successfully read
        if (bytes_read > 0) {
            // Remove trailing newline if present
            if ((*buf)[bytes_read - 1] == '\n') {
                (*buf)[bytes_read - 1] = '\0';
                bytes_read--;
            }

            // Set flags and perform additional processing
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);

            // Check for chained commands (separated by semicolons)
            if (_strchr(*buf, ';')) {
                *len = bytes_read;
                info->cmd_buf = *buf;
            }
        }
    }

    return bytes_read;
}
