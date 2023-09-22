#include "shell.h"

/**
 * _strcpy - string copy
 * @destination: the dest
 * @source: the src
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
	int j = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[j])
	{
		destination[j] = source[j];
		j++;
	}
	destination[j] = 0;
	return (destination);
}

/**
 * _strdup - string duplicate
 * @s: the s
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *s)
{
	int length = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--s;
	return (ret);
}

/**
 * _puts - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_putchar(s[j]);
		j++;
	}
}

/**
 * _putchar - char write
 * @c: The character
 * Return: On success 1.
 */
int _putchar(char c)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}
