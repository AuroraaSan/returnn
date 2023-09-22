#include "shell.h"

/**
 * history_display - displays the history list
 * @information: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int history_display(PassInfo_t *information)
{
	print_lst(information->hist);
	return (0);
}

/**
 * unset_alias -  unsets alias to string
 * @information: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(PassInfo_t *information, char *s)
{
	char *ptr, ch;
	int ret_prev;

	ptr = _searchar(s, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	ret_prev = delete_node(&(information->alias_node),
		get_index_of_node(information->alias_node,
		nd_starts_w(information->alias_node, s, -1)));
	*ptr = ch;
	return (ret_prev);
}

/**
 * set_alias - sets alias to string
 * @information: parameter struct
 * @s: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(PassInfo_t *information, char *s)
{
	char *ptr;

	ptr = _searchar(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(information, s));

	unset_alias(information, s);
	return (add_nodeto_end(&(information->alias_node), s, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(lst_t *node)
{
	char *ptr = NULL, *b = NULL;

	if (node)
	{
		ptr = _searchar(node->s, '=');
		for (b = node->s; b <= ptr; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * mimic_alias - mimics the alias builtin
 * @information: Struct contains potential args
 *
 *  Return: Always 0
 */
int mimic_alias(PassInfo_t *information)
{
	int x = 0;
	char *pointer = NULL;
	lst_t *node = NULL;

	if (information->a_counter == 1)
	{
		node = information->alias_node;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; information->a_value[x]; x++)
	{
		pointer = _searchar(information->a_value[x], '=');
		if (pointer)
			set_alias(information, information->a_value[x]);
		else
			print_alias(nd_starts_w(information->alias_node,
			information->a_value[x], '='));
	}

	return (0);
}
