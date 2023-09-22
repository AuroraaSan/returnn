#include "shell.h"

/**
 * print_error - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void print_error(char *s)
{
	int k = 0;

	if (!s)
		return;
	while (s[k] != '\0')
	{
		error_char(s[k]);
		k++;
	}
}

/**
 * error_char - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned
 */
int error_char(char ch)
{
	static int k;
	static char bufferr[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, bufferr, k);
		k = 0;
	}
	if (ch != BUF_FLUSH)
		bufferr[k++] = ch;
	return (1);
}

/**
 * write_to_fd - writes the character c to given fd
 * @ch: The character to print
 * @file_d: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned
 */
int write_to_fd(char ch, int file_d)
{
	static int k;
	static char bufferr[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(file_d, bufferr, k);
		k = 0;
	}
	if (ch != BUF_FLUSH)
		bufferr[k++] = ch;
	return (1);
}

/**
 * print_to_fd - prints an input string
 * @s: the string to be printed
 * @file_d: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int print_to_fd(char *s, int file_d)
{
	int k = 0;

	if (!s)
		return (0);
	while (*s)
	{
		k += write_to_fd(*s++, file_d);
	}
	return (k);
}

