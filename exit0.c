#include "shell.h"

int _myexit(info_t *info) {
    if (info->argv[1]) {  // Exit argument provided
        int exit_status = _erratoi(info->argv[1]);
        if (exit_status == -1) {
            // Handle invalid exit status
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = exit_status;
        return -2;  // Signal exit
    } else {
        info->err_num = -1;
        return -2;  // Signal exit without specific status
    }
}

int _mycd(info_t *info) {
    char *current_dir = getcwd(buffer, 1024);  // Get current directory
    if (!current_dir) {
        // Handle getcwd failure
        _puts("TODO: >>getcwd failure emsg here<<\n");
    }

    const char *target_dir;
    if (!info->argv[1]) {
        // No argument: Go to HOME or PWD
        target_dir = _getenv(info, "HOME=");
        if (!target_dir) {
            target_dir = _getenv(info, "PWD=");
            if (!target_dir) {
                target_dir = "/";  // Default to root
            }
        }
    } else if (_strcmp(info->argv[1], "-") == 0) {
        // Go to OLDPWD
        target_dir = _getenv(info, "OLDPWD=");
        if (!target_dir) {
            _puts(current_dir);
            _putchar('\n');
            return 1;  // No OLDPWD
        }
    } else {
        // Go to specified directory
        target_dir = info->argv[1];
    }

    if (chdir(target_dir) == -1) {
        print_error(info, "can't cd to ");
        _eputs(target_dir);
        _eputchar('\n');
    } else {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));  // Update PWD
    }

    return 0;
}

int _myhelp(info_t *info) {
    // Placeholder for future implementation
    _puts("help call works. Function not yet implemented \n");
    return 0;
}
