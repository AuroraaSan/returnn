
#include "shell.h"

/**
 * get_history_filepath - retrieves the path to the history file
 * @information: parameter structure
 * Return: allocated string containg history file
 */
char *get_history_filepath(PassInfo_t *information)
{
	char *buffer, *direct;

	direct = get_env_value(information, "HOME=");
	if (!direct)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(direct) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, direct);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * w_history - creates or appends to a history file
 * @information: parameter structure
 * Return: 1 on success, -1 on failure
 */
int w_history(PassInfo_t *information)
{
	ssize_t f_d;
	char *filen = get_history_filepath(information);
	lst_t *node = NULL;

	if (!filen)
		return (-1);

	f_d = open(filen, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filen);
	if (f_d == -1)
		return (-1);
	for (node = information->hist; node; node = node->next)
	{
		print_to_fd(node->s, f_d);
		write_to_fd('\n', f_d);
	}
	write_to_fd(BUF_FLUSH, f_d);
	close(f_d);
	return (1);
}

/**
 * r_history - reads history from file
 * @information: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int r_history(PassInfo_t *information)
{
	int i, las = 0, line_count = 0;
	ssize_t f_d,  read_length, fsize = 0;
	struct stat st;
	char *buff = NULL, *filen = get_history_filepath(information);

	if (!filen)
		return (0);

	f_d = open(filen, O_RDONLY);
	free(filen);
	if (f_d == -1)
		return (0);
	if (!fstat(f_d, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	read_length = read(f_d, buff, fsize);
	buff[fsize] = 0;
	if (read_length <= 0)
		return (free(buff), 0);
	close(f_d);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_hlist(information, buff + las, line_count++);
			las = i + 1;
		}
	if (las != i)
		build_hlist(information, buff + las, line_count++);
	free(buff);
	information->history_line_count = line_count;
	while (information->history_line_count-- >= HIST_MAX)
		delete_node(&(information->hist), 0);
	renum_hist(information);
	return (information->history_line_count);
}

/**
 * build_hlist - appends an entry to the history linked list
 * @information: parameter structure
 * @buff: buffer containing the history entry
 * @linecount: the history line count
 * Return: Always 0
 */
int build_hlist(PassInfo_t *information, char *buff, int linecount)
{
	lst_t *node = NULL;

	if (information->hist)
		node = information->hist;
	add_nodeto_end(&node, buff, linecount);

	if (!information->hist)
		information->hist = node;
	return (0);
}

/**
 * renum_hist - renumbers the history linked list after changes
 * @information: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_hist(PassInfo_t *information)
{
	lst_t *node = information->hist;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (information->history_line_count = i);
}
