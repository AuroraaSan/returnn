#include "shell.h"

/**
 * copy_environ_to_string_array - returns the string array of env
 * @information: Structure containing potential arguments.
 * Return: Always 0
 */
char **copy_environ_to_string_array(PassInfo_t *information)
{
	if (!information->environ || information->environment_changed)
	{
		information->environ = lst_to_strings(information->environment_list);
		information->environment_changed = 0;
	}

	return (information->environ);
}

/**
 * delete_env_var - Remove environment variable
 * @information: Structure containing potential arguments.
 * @v: the string env var property
 *
 *  Return: 1 on delete, 0 otherwise
 */
int delete_env_var(PassInfo_t *information, char *v)
{
	lst_t *nod = information->environment_list;
	size_t i = 0;
	char *p;

	if (!nod || !v)
		return (0);

	while (nod)
	{
		p = starts_w(nod->s, v);
		if (p && *p == '=')
		{
			information->environment_changed =
				delete_node(&(information->environment_list), i);
			i = 0;
			nod = information->environment_list;
			continue;
		}
		nod = nod->next;
		i++;
	}
	return (information->environment_changed);
}

/**
 * set_env_variable - Initialize a new environment variable,
 *             or modify an existing one
 * @information: Structure containing potential arguments.
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int set_env_variable(PassInfo_t *information, char *v, char *val)
{
	char *bufferr = NULL;
	lst_t *nod;
	char *p;

	if (!v || !val)
		return (0);

	bufferr = malloc(_strlen(v) + _strlen(val) + 2);
	if (!bufferr)
		return (1);
	_strcpy(bufferr, v);
	_strcat(bufferr, "=");
	_strcat(bufferr, val);
	nod = information->environment_list;
	while (nod)
	{
		p = starts_w(nod->s, v);
		if (p && *p == '=')
		{
			free(nod->s);
			nod->s = bufferr;
			information->environment_changed = 1;
			return (0);
		}
		nod = nod->next;
	}
	add_nodeto_end(&(information->environment_list), bufferr, 0);
	free(bufferr);
	information->environment_changed = 1;
	return (0);
}

