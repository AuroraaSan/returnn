#include "shell.h"

/**
 * main - entry point
 * @a_c: arg count
 * @a_v: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int a_c, char **a_v)
{
	PassInfo_t information[] = { INFO_INIT };
	int f_d = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f_d)
			: "r" (f_d));

	if (a_c == 2)
	{
		f_d = open(a_v[1], O_RDONLY);
		if (f_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_error(a_v[0]);
				print_error(": 0: Can't open ");
				print_error(a_v[1]);
				error_char('\n');
				error_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->read_file_descriptor = f_d;
	}
	populate_env_lst(information);
	r_history(information);
	hsh(information, a_v);
	return (EXIT_SUCCESS);
}
