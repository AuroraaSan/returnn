#include "shell.h"

/**
 * *node_addition_start - adds a node to the start of the list
 * @h: address of pointer to head node
 * @s: str field of node
 * @nm: node index used by history
 *
 * Return: size of list
 */
lst_t *node_addition_start(lst_t **h, const char *s, int nm)
{
	lst_t *new_h;

	/*check for list first*/
	if (!h)
		return (NULL);
	new_h = malloc(sizeof(lst_t));
	if (!new_h)
		return (NULL);
	_set_memory((void *)new_h, 0, sizeof(lst_t));
	new_h->n = nm;
	if (s)
	{
		new_h->s = _strdup(s);
		if (!new_h->s)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *h;
	*h = new_h;
	return (new_h);
}

/**
 * add_nodeto_end - adds a node to the end of the list
 * @h: address of pointer to head node
 * @s: str field of node
 * @nm: node index used by history
 *
 * Return: size of list
 */
lst_t *add_nodeto_end(lst_t **h, const char *s, int nm)
{
	lst_t *new_nod, *nod;

	if (!h)
		return (NULL);

	nod = *h;
	new_nod = malloc(sizeof(lst_t));
	if (!new_nod)
		return (NULL);
	_set_memory((void *)new_nod, 0, sizeof(lst_t));
	new_nod->n = nm;
	if (s)
	{
		new_nod->s = _strdup(s);
		if (!new_nod->s)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*h = new_nod;
	return (new_nod);
}

/**
 * print_lst_str - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_lst_str(const lst_t *head)
{
	size_t x = 0;

	while (head)
	{
		_puts(head->s ? head->s : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}

/**
 * delete_node - deletes node at given index
 * @h: address of pointer to first node
 * @idx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node(lst_t **h, unsigned int idx)
{
	lst_t *nod, *prv_nod;
	unsigned int k = 0;

	if (!h || !*h)
		return (0);

	if (!idx)
	{
		nod = *h;
		*h = (*h)->next;
		free(nod->s);
		free(nod);
		return (1);
	}
	nod = *h;
	while (nod)
	{
		if (k == idx)
		{
			prv_nod->next = nod->next;
			free(nod->s);
			free(nod);
			return (1);
		}
		k++;
		prv_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * free_lst - frees all nodes of a list
 * @h_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_lst(lst_t **h_ptr)
{
	lst_t *nod, *nxt_nod, *h;

	/*check if pointer exists first*/
	if (!h_ptr || !*h_ptr)
		return;
	/*set temp for pointer and assign node to temp*/
	h = *h_ptr;
	nod = h;
	/*iterate to free nodes in list*/
	while (nod)
	{
		nxt_nod = nod->next;
		free(nod->s);
		free(nod);
		nod = nxt_nod;
	}
	/*set pointer to null*/
	*h_ptr = NULL;
}

