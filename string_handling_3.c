#include "shell.h"

/**
 **_strcpy_n - copy a string with certain bytes
 * @destination: dest
 * @source: source
 *@num: amount of char
 * Return: pointer
 */
char *_strcpy_n(char *destination, char *source, int num)
{
	int x, y;
	char *l = destination;

	x = 0;
	while (source[x] != '\0' && x < num - 1)
	{
		destination[x] = source[x];
		x++;
	}
	if (x < num)
	{
		y = x;
		while (y < num)
		{
			destination[y] = '\0';
			y++;
		}
	}
	return (l);
}

/**
 * _strcat_n - concatenated strings with certain bytes
 * @destination: dest
 * @source: source
 *@num: the amount of bytes
 *Return: pointer
 */
char *_strcat_n(char *destination, char *source, int num)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < num)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < num)
		destination[i] = '\0';
	return (s);
}

/**
 **_searchar - search for a char in string
 * @str: string
 *@ch: char
 *Return: pointer
 */
char *_searchar(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
