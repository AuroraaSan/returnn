#include "shell.h"
#include <signal.h>

/**
 * input_buf - buffers commands
 * @information: parameter struct
 * @buff: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(PassInfo_t *information, char **buff, size_t *len)
{
	ssize_t x = 0;
	size_t ptr_len = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, handle_cmd_ctrl);
#if USE_GETLINE
		x = getline(buff, &ptr_len, stdin);
#else
		x = input_line_get(information, buff, &ptr_len);
#endif
		if (x > 0)
		{
			if ((*buff)[x - 1] == '\n')
			{
				(*buff)[x - 1] = '\0';
				x--;
			}
			information->count_this_line = 1;
			comments_handling(*buff);
			build_hlist(information, *buff, information->history_line_count++);
			{
				*len = x;
				information->cmd_buffer = buff;
			}
		}
	}
	return (x);
}

/**
 * record_user_input - gets a line minus the newline
 * @information: parameter struct
 *
 * Return: bytes read
 */
ssize_t record_user_input(PassInfo_t *information)
{
	static char *buff;
	static size_t x, y, lenn;
	ssize_t z = 0;
	char **buf_pos = &(information->argument), *ptr;

	_putchar(BUF_FLUSH);
	z = input_buf(information, &buff, &lenn);
	if (z == -1)
		return (-1);
	if (lenn)
	{
		y = x;
		ptr = buff + x;

		check_chain_conditions(information, buff, &y, x, lenn);
		while (y < lenn)
		{
			if (isChain(information, buff, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= lenn)
		{
			x = lenn = 0;
			information->cmd_buffer_type = CMD_NORM;
		}

		*buf_pos = ptr;
		return (_strlen(ptr));
	}

	*buf_pos = buff;
	return (z);
}

/**
 * read_buf - reads a buffer
 * @information: parameter struct
 * @buffer: buffer
 * @x: size
 * Return: y
 */
ssize_t read_buf(PassInfo_t *information, char *buffer, size_t *x)
{
	ssize_t y = 0;

	if (*x)
		return (0);
	y = read(information->read_file_descriptor, buffer, READ_BUF_SIZE);
	if (y >= 0)
		*x = y;
	return (y);
}

/**
 * input_line_get - gets the next line of input from STDIN
 * @information: parameter struct
 * @p: address of pointer to buf
 * @len: size ptr
 *
 * Return: s
 */
int input_line_get(PassInfo_t *information, char **p, size_t *len)
{
	static char buffer[READ_BUF_SIZE];
	static size_t x, lenn;
	size_t y;
	ssize_t r = 0, q = 0;
	char *ptr = NULL, *neww = NULL, *ch;

	ptr = *p;
	if (ptr && len)
		q = *len;
	if (x == lenn)
		x = lenn = 0;

	r = read_buf(information, buffer, &lenn);
	if (r == -1 || (r == 0 && lenn == 0))
		return (-1);

	ch = _searchar(buffer + x, '\n');
	y = ch ? 1 + (unsigned int)(ch - buffer) : lenn;
	neww = _memory_reallocate(ptr, q, q ? q + y : y + 1);
	if (!neww)
		return (ptr ? free(ptr), -1 : -1);

	if (q)
		_strcat_n(neww, buffer + x, y - x);
	else
		_strcpy_n(neww, buffer + x, y - x + 1);

	q += y - x;
	x = y;
	ptr = neww;

	if (len)
		*len = q;
	*p = ptr;
	return (q);
}

/**
 * handle_cmd_ctrl - handles commands
 * @signal_n: the signal number
 *
 * Return: void
 */
void handle_cmd_ctrl(__attribute__((unused))int signal_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
