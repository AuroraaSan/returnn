#include "shell.h"

/**
 * print_env - prints the current environment
 * @information: Structure inf
 * Return: Always 0
 */
int print_env(PassInfo_t *information)
{
	print_lst_str(information->environment_list);
	return (0);
}

/**
 * get_env_value - gets the value of an environ variable
 * @information: Structure containing potential arguments.
 * @nm: env var name
 *
 * Return: the value
 */
char *get_env_value(PassInfo_t *information, const char *nm)
{
	lst_t *nd = information->environment_list;
	char *ptr;

	while (nd)
	{
		ptr = starts_w(nd->s, nm);
		if (ptr && *ptr)
			return (ptr);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * set_env_var - Initialize a new environment variable,
 * @information: Structure containing potential arguments.
 *  Return: Always 0
 */
int set_env_var(PassInfo_t *information)
{
	if (information->a_counter != 3)
	{
		print_error("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env_variable(information, information->a_value[1],
				information->a_value[2]))
		return (0);
	return (1);
}

/**
 * unset_env_var - Remove an environment variable
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unset_env_var(PassInfo_t *information)
{
	int x;

	if (information->a_counter == 1)
	{
		print_error("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= information->a_counter; x++)
		delete_env_var(information, information->a_value[x]);

	return (0);
}

/**
 * populate_env_lst - populates env linked list
 * @information: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_lst(PassInfo_t *information)
{
	lst_t *nod = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_nodeto_end(&nod, environ[x], 0);
	information->environment_list = nod;
	return (0);
}

