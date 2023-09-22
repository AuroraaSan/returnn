#include "shell.h"

/**
 * hsh - main shell loop
 * @information: the parameter & return info struct
 * @a_val: the argument vector from main()
 *
 * Return: 0 on success, 1 on error
 */
int hsh(PassInfo_t *information, char **a_val)
{
	ssize_t m = 0;
	int built_ret = 0;

	while (m != -1 && built_ret != -2)
	{
		clear_shell_info(information);
		if (mode_interact(information))
			_puts("$ ");
		error_char(BUF_FLUSH);
		m = record_user_input(information);
		if (m != -1)
		{
			set_shell_info(information, a_val);
			built_ret = builtinFind(information);
			if (built_ret == -1)
				cmdFind(information);
		}
		else if (mode_interact(information))
			_putchar('\n');
		free_shell_info(information, 0);
	}
	w_history(information);
	free_shell_info(information, 1);
	if (!mode_interact(information) && information->return_status)
		exit(information->return_status);
	if (built_ret == -2)
	{
		if (information->error_number == -1)
			exit(information->return_status);
		exit(information->error_number);
	}
	return (built_ret);
}

/**
 * builtinFind - finds a builtin command
 * @information: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int builtinFind(PassInfo_t *information)
{
	int x, built_ret = -1;
	table_t builttbl[] = {
		{"exit", _xit},
		{"env", print_env},
		{"help", _help},
		{"history", history_display},
		{"setenv", set_env_var},
		{"unsetenv", unset_env_var},
		{"cd", _cd},
		{"alias", mimic_alias},
		{NULL, NULL}
	};

	for (x = 0; builttbl[x].typo; x++)
		if (_strcmp(information->a_value[0], builttbl[x].typo) == 0)
		{
			information->error_count++;
			built_ret = builttbl[x].function(information);
			break;
		}
	return (built_ret);
}

/**
 * cmdFind - finds a command in PATH
 * @information: the parameter & return info struct
 *
 * Return: void
 */
void cmdFind(PassInfo_t *information)
{
	char *path = NULL;
	int i, k;

	information->path = information->a_value[0];
	if (information->count_this_line == 1)
	{
		information->error_count++;
		information->count_this_line = 0;
	}
	for (i = 0, k = 0; information->argument[i]; i++)
		if (!is_char_delim(information->argument[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = get_path(information, get_env_value(information, "PATH="),
			information->a_value[0]);
	if (path)
	{
		information->path = path;
		cmdFork(information);
	}
	else
	{
		if ((mode_interact(information) || get_env_value(information, "PATH=") ||
					information->a_value[0][0] == '/') && check_ex_commad(information,
						information->a_value[0]))
			cmdFork(information);
		else if (*(information->argument) != '\n')
		{
			information->return_status = 127;
			error_handling(information, "not found\n");
		}
	}
}

/**
 * cmdFork - forks exec thread to run cmd
 * @information: the parameter & return info struct
 *
 * Return: void
 */
void cmdFork(PassInfo_t *information)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(information->path, information->a_value,
					copy_environ_to_string_array(information)) == -1)
		{
			free_shell_info(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(information->return_status));
		if (WIFEXITED(information->return_status))
		{
			information->return_status = WEXITSTATUS(information->return_status);
			if (information->return_status == 126)
				error_handling(information, "Permission denied\n");
		}
	}
}

