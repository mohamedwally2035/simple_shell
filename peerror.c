#include "shell.h"

/**
 * _eputs - prints a string of input
 * @str: a string that will be printed
 *
 * Return: NULL
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}


/**
 * _eputchar - adds the char C to stderr.
 * @c: The text to be printed
 *
 * Return: On success 1.
 * On error, Errno is set properly and -1 is returned.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}


/**
 * _putfd - writes the letter C to the specified fd.
 * @c: The char to print
 * @fd: The address to write to is
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
static char buf[WRITE_BUF_SIZE];
static int buf_index;

if (c == '\n' || buf_index >= WRITE_BUF_SIZE)
{
if (write(fd, buf, buf_index) < 0)
{
return (-1);
}
buf_index = 0;
}

if (c != '\n')
{
buf[buf_index++] = c;
}

return (1);
}

/**
 * _putsfd - prints a string of input
 * @str: a string that will be printed
 * @fd: The address to contact is
 *
 * Return: amount of characters entered
 */
int _putsfd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);

for (; *str; str++)
{
i += _putfd(*str, fd);
}

return (i);
}

