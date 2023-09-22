#include "shell.h"

/**
 * mode_interact - chek if shell is interactive
 * @information: struct address
 *
 * Return: 1 or 0
 */
int mode_interact(PassInfo_t *information)
{
	/*return statement to check if the shell is interactive*/
	return (isatty(STDIN_FILENO) && information->read_file_descriptor <= 2);
}

/**
 * is_char_delim - checks if character delimeter
 * @ch: the char
 * @delm: delimeter string
 * Return: 1 if true or 0 if false
 */
int is_char_delim(char ch, char *delm)
{
	while (*delm)
		if (*delm++ == ch)
			return (1);
	return (0);
}

/**
 * _is_char_alphabatic - checks for alphabetic character
 * @ch: The character to input
 * Return: 1 if correct or 0
 */

int _is_char_alphabatic(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _str_to_int(char *s)
{
	int x, sgn = 1, flg = 0, out;
	unsigned int res = 0;

	for (x = 0; s[x] != '\0' && flg != 2; x++)
	{
		if (s[x] == '-')
			sgn *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			flg = 1;
			res *= 10;
			res += (s[x] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sgn == -1)
		out = -res;
	else
		out = res;

	return (out);
}

