
#include "shell.h"

/**
 * get_length - determines length of linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t get_length(const lst_t *ptr)
{
	size_t x = 0;

	while (ptr)
	{
		ptr = ptr->next;
		x++;
	}
	return (x);
}

/**
 * lst_to_strings - returns an array of strings of the list->str
 * @h: pointer to first node
 *
 * Return: array of strings
 */
char **lst_to_strings(lst_t *h)
{
	lst_t *nod = h;
	size_t x = get_length(h), j;
	char **srs;
	char *s;

	if (!h || !x)
		return (NULL);
	srs = malloc(sizeof(char *) * (x + 1));
	if (!srs)
		return (NULL);
	for (x = 0; nod; nod = nod->next, x++)
	{
		s = malloc(_strlen(nod->s) + 1);
		if (!s)
		{
			for (j = 0; j < x; j++)
				free(srs[j]);
			free(srs);
			return (NULL);
		}

		s = _strcpy(s, nod->s);
		srs[x] = s;
	}
	srs[x] = NULL;
	return (srs);
}


/**
 * print_lst - prints all elements of a list_t linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t print_lst(const lst_t *ptr)
{
	size_t x = 0;

	while (ptr)
	{
		_puts(number_to_str(ptr->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr->s ? ptr->s : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		x++;
	}
	return (x);
}

/**
 * nd_starts_w - returns node whose string starts with prefix
 * @nd: pointer to list head
 * @pfix: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */
lst_t *nd_starts_w(lst_t *nd, char *pfix, char ch)
{
	char *pr = NULL;

	while (nd)
	{
		pr = starts_w(nd->s, pfix);
		if (pr && ((ch == -1) || (*pr == ch)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * get_index_of_node - gets the index of a node
 * @h: pointer to list head
 * @nd: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_index_of_node(lst_t *h, lst_t *nd)
{
	size_t x = 0;

	while (h)
	{
		if (h == nd)
			return (x);
		h = h->next;
		x++;
	}
	return (-1);
}

