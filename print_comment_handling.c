#include "shell.h"

/**
 * _str_to_int_witherror - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string or 0 on faliure
 */
int _str_to_int_witherror(char *s)
{
	int x = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (x = 0;  s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			res *= 10;
			res += (s[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * error_handling - prints error message
 * @information: the parameter & return info struct
 * @s: string containing specified error type
 * Return: 0 if no numbers in string
 */
void error_handling(PassInfo_t *information, char *s)
{
	print_error(information->file_name);
	print_error(": ");
	decimal_print(information->error_count, STDERR_FILENO);
	print_error(": ");
	print_error(information->a_value[0]);
	print_error(": ");
	print_error(s);
}

/**
 * decimal_print - function prints a decimal int (base 10)
 * @in: input
 * @file_d: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int decimal_print(int in, int file_d)
{
	int (*__putchar)(char) = _putchar;
	int i, ct = 0;
	unsigned int _abs_, curr;

	if (file_d == STDERR_FILENO)
		__putchar = error_char;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		ct++;
	}
	else
		_abs_ = in;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			ct++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	ct++;

	return (ct);
}

/**
 * number_to_str - converter function, a clone of itoa
 * @nm: number
 * @b: base
 * @flgs: argument flags
 *
 * Return: string
 */
char *number_to_str(long int nm, int b, int flgs)
{
	static char *array;
	static char buffer[50];
	char sg = 0;
	char *pr;
	unsigned long n = nm;

	if (!(flgs & CONVERT_UNSIGNED) && nm < 0)
	{
		n = -nm;
		sg = '-';

	}
	array = flgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pr = &buffer[49];
	*pr = '\0';

	do	{
		*--pr = array[n % b];
		n /= b;
	} while (n != 0);

	if (sg)
		*--pr = sg;
	return (pr);
}

/**
 *  comments_handling - function replaces '#' with '\0'
 * @bufferr: address of the string to modify
 *
 * Return: Always 0;
 */
void comments_handling(char *bufferr)
{
	int x;

	for (x = 0; bufferr[x] != '\0'; x++)
		if (bufferr[x] == '#' && (!x || bufferr[x - 1] == ' '))
		{
			bufferr[x] = '\0';
			break;
		}
}

