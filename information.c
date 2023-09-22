#include "shell.h"

/**
 * clear_shell_info - initializes info_t struct
 * @information: struct address
 */
void clear_shell_info(PassInfo_t *information)
{
	information->argument = NULL;
	information->a_value = NULL;
	information->path = NULL;
	information->a_counter = 0;
}

/**
 * set_shell_info - initializes info_t struct
 * @information: struct address
 * @a_val: argument vector
 */
void set_shell_info(PassInfo_t *information, char **a_val)
{
	int i = 0;

	information->file_name = a_val[0];
	if (information->argument)
	{
		information->a_value = string_to_word(information->argument, " \t");
		if (!information->a_value)
		{
			information->a_value = malloc(sizeof(char *) * 2);
			if (information->a_value)
			{
				information->a_value[0] = _strdup(information->argument);
				information->a_value[1] = NULL;
			}
		}
		for (i = 0; information->a_value && information->a_value[i]; i++)
			;
		information->a_counter = i;

		replace_aliases(information);
		replace_variables(information);
	}
}

/**
 * free_shell_info - frees info_t struct fields
 * @information: struct address
 * @all_f: true if freeing all fields
 */
void free_shell_info(PassInfo_t *information, int all_f)
{
	free_string(information->a_value);
	information->a_value = NULL;
	information->path = NULL;
	if (all_f)
	{
		if (!information->cmd_buffer)
			free(information->argument);
		if (information->environment_list)
			free_lst(&(information->environment_list));
		if (information->hist)
			free_lst(&(information->hist));
		if (information->alias_node)
			free_lst(&(information->alias_node));
		free_string(information->environ);
			information->environ = NULL;
		free_pointer((void **)information->cmd_buffer);
		if (information->read_file_descriptor > 2)
			close(information->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}

