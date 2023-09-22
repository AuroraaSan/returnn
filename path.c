#include "shell.h"

/**
 * check_ex_commad - determines if a file is an executable command
 * @information: the info struct
 * @path: path to the file
 *
 * Return: 1 or 0 otherwise
 */
int check_ex_commad(PassInfo_t *information, char *path)
{
	struct stat stt;

	(void)information;
	if (!path || stat(path, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * characters_duplicate - duplicates characters
 * @pathstrr: the PATH string
 * @first: starting index
 * @end: stopping index
 *
 * Return: pointer to new buffer
 */
char *characters_duplicate(char *pathstrr, int first, int end)
{
	static char bufferr[1024];
	int x = 0, m = 0;

	for (m = 0, x = first; x < end; x++)
		if (pathstrr[x] != ':')
			bufferr[m++] = pathstrr[x];
	bufferr[m] = 0;
	return (bufferr);
}

/**
 * get_path - finds this cmd in the PATH string
 * @information: the info struct
 * @pathstrr: the PATH string
 * @cmdd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *get_path(PassInfo_t *information, char *pathstrr, char *cmdd)
{
	int i = 0, current_p = 0;
	char *path;

	if (!pathstrr)
		return (NULL);
	if ((_strlen(cmdd) > 2) && starts_w(cmdd, "./"))
	{
		if (check_ex_commad(information, cmdd))
			return (cmdd);
	}
	while (1)
	{
		if (!pathstrr[i] || pathstrr[i] == ':')
		{
			path = characters_duplicate(pathstrr, current_p, i);
			if (!*path)
				_strcat(path, cmdd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmdd);
			}
			if (check_ex_commad(information, path))
				return (path);
			if (!pathstrr[i])
				break;
			current_p = i;
		}
		i++;
	}
	return (NULL);
}


