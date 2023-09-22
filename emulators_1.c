#include "shell.h"

/**
 * _xit - used to exit the shell
 * @information: Used to maintain the constant function.
 * Return: exits
 */
int _xit(PassInfo_t *information)
{
	int checkexit;

	if (information->a_value[1]) 
	{
		checkexit = _str_to_int_witherror(information->a_value[1]);
		if (checkexit == -1)
		{
			information->return_status = 2;
			error_handling(information, "Illegal number: ");
			print_error(information->a_value[1]);
			error_char('\n');
			return (1);
		}
		information->error_number = _str_to_int_witherror(information->a_value[1]);
		return (-2);
	}
	information->error_number = -1;
	return (-2);
}

/**
 * _cd - changes the current directory of the process
 * @information: Used to maintain the constant function.
 * Return: 0
 */
int _cd(PassInfo_t *information)
{
	char *s, *direction, buff[1024];
	int ret_Chdir;

	s = getcwd(buff, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!information->a_value[1])
	{
		direction = get_env_value(information, "HOME=");
		if (!direction)
			ret_Chdir = 
				chdir((direction = get_env_value(information, "PWD=")) ? direction : "/");
		else
			ret_Chdir = chdir(direction);
	}
	else if (_strcmp(information->a_value[1], "-") == 0)
	{
		if (!get_env_value(information, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env_value(information, "OLDPWD=")), _putchar('\n');
		ret_Chdir = 
			chdir((direction = get_env_value(information, "OLDPWD=")) ? direction : "/");
	}
	else
		ret_Chdir = chdir(information->a_value[1]);
	if (ret_Chdir == -1)
	{
		error_handling(information, "can't cd to ");
		print_error(information->a_value[1]), error_char('\n');
	}
	else
	{
		set_env_variable(information, "OLDPWD", get_env_value(information, "PWD="));
		set_env_variable(information, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _help - changes the current directory 
 * @information: Used to maintain the constant function.
 * Return:  0
 */
int _help(PassInfo_t *information)
{
	char **a_array;

	a_array = information->a_value;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*a_array); 
	return (0);
}
