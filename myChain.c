#include "shell.h"

/**
 * isChain - checks if the current char in the buffer is chain delimiter
 * @information: the parameter struct
 * @buff: the char buffer
 * @p: Address of the current position in buffer
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int isChain(PassInfo_t *information, char *buff, size_t *p)
{
	size_t i = *p;

	if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buff[i] = 0;
		i++;
		information->cmd_buffer_type = CMD_OR;
	}
	else if (buff[i] == '&' && buff[i + 1] == '&')
	{
		buff[i] = 0;
		i++;
		information->cmd_buffer_type = CMD_AND;
	}
	else if (buff[i] == ';')
	{
		buff[i] = 0;
		information->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * check_chain_conditions - Check to continue chaining or not
 * @information: the parameter struct
 * @buff:The character buffer
 * @p: Address of the current position in buffer
 * @i: Starting position in buffer
 * @len: length of buf
 * Return: Void
 */
void check_chain_conditions(PassInfo_t *information,
	       char *buff, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (information->cmd_buffer_type == CMD_AND)
	{
		if (information->return_status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (information->cmd_buffer_type == CMD_OR)
	{
		if (!information->return_status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_aliases - Replaces an alias in the tokenized string.
 * @information: The parameter structure.
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_aliases(PassInfo_t *information)
{
	int j;
	lst_t *node;
	char *k;

	for (j = 0; j < 10; j++)
	{
		node = nd_starts_w(information->alias_node, information->a_value[0], '=');
		if (!node)
			return (0);
		free(information->a_value[0]);
		k = _searchar(node->s, '=');
		if (!k)
			return (0);
		k = _strdup(k + 1);
		if (!k)
			return (0);
		information->a_value[0] = k;
	}
	return (1);
}

/**
 * replace_variables - Replaces variables in the tokenized string.
 * @information: The parameter structure.
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(PassInfo_t *information)
{
	int j = 0;
	lst_t *node;

	for (j = 0; information->a_value[j]; j++)
	{
		if (information->a_value[j][0] != '$' || !information->a_value[j][1])
			continue;

		if (!_strcmp(information->a_value[j], "$?"))
		{
			string_replace(&(information->a_value[j]),
					_strdup(number_to_str(information->return_status, 10, 0)));
			continue;
		}
		if (!_strcmp(information->a_value[j], "$$"))
		{
			string_replace(&(information->a_value[j]),
					_strdup(number_to_str(getpid(), 10, 0)));
			continue;
		}
		node = nd_starts_w(information->environment_list,
		&information->a_value[j][1], '=');
		if (node)
		{
			string_replace(&(information->a_value[j]),
					_strdup(_searchar(node->s, '=') + 1));
			continue;
		}
		string_replace(&information->a_value[j], _strdup(""));

	}
	return (0);
}

/**
 * string_replace - Replaces a string.
 * @oldy: Address of the old string.
 * @neww: New string.
 * Return: 1 if replaced, 0 otherwise
 */
int string_replace(char **oldy, char *neww)
{
	free(*oldy);
	*oldy = neww;
	return (1);
}
