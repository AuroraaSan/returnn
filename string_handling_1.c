#include "shell.h"

/**
 * _strlen - it returns the len of string
 * @s: the needed stringg
 * Return: string len
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - it compares two strings
 * @s1: string number 1
 * @s2: string number 2
 * Return: negative or positive or zero
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_w - checks if needle starts with haystack
 * @hay: string we want to search for
 * @ndl: substring we want to find 
 * Return: address of next char of haystack or NULL
 */
char *starts_w(const char *hay, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * _strcat - adds two string
 * @destination: dest buffer
 * @source:  src buffer
 * Return: pointer of (destination) buffer
 */
char *_strcat(char *destination, char *source)
{
	char *ans = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ans);
}
