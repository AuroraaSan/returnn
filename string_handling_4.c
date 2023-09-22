#include "shell.h"

/**
 * **string_to_word - splits a string into words. Repeat delimiters are ignored
 * @s: the input string
 * @delm: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_to_word(char *s, char *delm)
{
	int i, j, k, m, num = 0;
	char **sr;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!delm)
		delm = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!is_char_delim(s[i], delm) && (is_char_delim(s[i + 1], delm) || !s[i + 1]))
			num++;

	if (num == 0)
		return (NULL);
	sr = malloc((1 + num) * sizeof(char *));
	if (!sr)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_char_delim(s[i], delm))
			i++;
		k = 0;
		while (!is_char_delim(s[i + k], delm) && s[i + k])
			k++;
		sr[j] = malloc((k + 1) * sizeof(char));
		if (!sr[j])
		{
			for (k = 0; k < j; k++)
				free(sr[k]);
			free(sr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sr[j][m] = s[i++];
		sr[j][m] = 0;
	}
	sr[j] = NULL;
	return (sr);
}

/**
 * string_to_word_ecounter - splits a string into words
 * @s: the input string
 * @delm: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **string_to_word_ecounter(char *s, char delm)
{
	int i, j, k, m, num = 0;
	char **sr;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != delm && s[i + 1] == delm) ||
				    (s[i] != delm && !s[i + 1]) || s[i + 1] == delm)
			num++;
	if (num == 0)
		return (NULL);
	sr = malloc((1 + num) * sizeof(char *));
	if (!sr)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (s[i] == delm && s[i] != delm)
			i++;
		k = 0;
		while (s[i + k] != delm && s[i + k] && s[i + k] != delm)
			k++;
		sr[j] = malloc((k + 1) * sizeof(char));
		if (!sr[j])
		{
			for (k = 0; k < j; k++)
				free(sr[k]);
			free(sr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sr[j][m] = s[i++];
		sr[j][m] = 0;
	}
	sr[j] = NULL;
	return (sr);
}

