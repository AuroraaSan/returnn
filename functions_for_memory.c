#include "shell.h"

/**
 * _set_memory - fills memory with a constant byte
 * @mem: the pointer to the memory area
 * @b: the byte to fill *s with
 * @num: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_set_memory(char *mem, char b, unsigned int num)
{
	unsigned int j;

	for (j = 0; j < num; j++)
		mem[i] = b;
	return (mem);
}

/**
 * free_string - frees a string of strings
 * @p: string
 */
void free_string(char **p)
{
	char **b = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(b);
}

/**
 * *_memory_reallocate - reallocates  memory
 * @ptr: previous malloc'ated block pointer
 * @oldy: size of byte previous block
 * @neww: size of byte new block
 *
 * Return: pointer to da ol'block nameen.
 */
void **_memory_reallocate(void *ptr, unsigned int oldy, unsigned int neww)
{
	char *p;

	if (!ptr)
		return (malloc(neww));
	if (!neww)
		return (free(ptr), NULL);
	if (neww == oldy)
		return (ptr);

	p = malloc(neww);
	if (!p)
		return (NULL);

	oldy = oldy < neww ? oldy : neww;
	while (oldy--)
		p[oldy] = ((char *)ptr)[oldy];
	free(ptr);
	return (p);
}
