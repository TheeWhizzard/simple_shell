#include "shell.h"

/**
 * custom_exit - Exits the shell
 * @info: Structure containing potential arguments.
 *
 * Return: Returns -2 to signal the shell to exit.
 * If info->argv[1] is provided and represents a valid integer,
 * the error code is set accordingly.
 * If the provided argument is not a valid integer, an error message
 * is printed, and the status is set to 2.
 */
int custom_exit(info_t *info)
{
	if (info->argv[1])
	{
		int exit_status = _custom_atoi(info->argv[1]);

		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_custom_puts(info->argv[1]);
			_custom_putchar('\n');
			return (1);
		}
		info->error_code = exit_status;
	}
	return (-2);
}
/**
 * custom_cd - Handles the "cd" command to change the working directory.
 * @info: Structure containing potential arguments.
 *
 * This function processes the "cd" command, allowing the user to change
 * the current working directory. It updates the environment variables
 * "OLDPWD" and "PWD" accordingly.
 *
 * Return: Always returns 0.
 * If the provided argument is "-", the function switches to the previous
 * directory recorded in "OLDPWD". If no argument is provided, it changes
 * to the home directory. In case of errors, appropriate error messages
 * are printed.
 */
int custom_cd(info_t *info)
{
	char buffer[1024], *target_dir;
	char *current_dir = _custom_getcwd(buffer, 1024);

	if (!current_dir)
		_custom_puts("Error: Unable to get current directory.\n");
	else if (!info->argv[1])
	{
		target_dir = _custom_getenv(info, "HOME=");

		if (!target_dir)
			chdir_result = chdir((target_dir = _custom_getenv(info, "PWD="))
					? target_dir : "/");
		else
			chdir_result = chdir(target_dir);
	}
	else if (_custom_strcmp(info->argv[1], "-") == 0)
	{
		target_dir = _custom_getenv(info, "OLDPWD=");
		if (!target_dir)
			_custom_puts(current_dir);
		else
			_custom_puts(_custom_getenv(info, "OLDPWD="));
		chdir_result = chdir((target_dir = _custom_getenv(info, "OLDPWD="))
				? target_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		print_error(info, "Error: Unable to change directory to ");
		_custom_puts(info->argv[1]);
		_custom_putchar('\n');
	}
	else
	{
		_custom_setenv(info, "OLDPWD", _custom_getenv(info, "PWD="));
		_custom_setenv(info, "PWD", _custom_getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * custom_help - Provides help information for the shell.
 * @info: Structure containing potential arguments.
 *
 * This function displays a help message about the shell program.
 * It also prints the command that was entered by the user.
 *
 * Return: Always returns 0.
 */
int custom_help(info_t *info)
{
	_custom_puts("Help: This is a simple shell program.\n");

	if (info->argv[0])
	{
		_custom_puts("You entered: ");
		_custom_puts(info->argv[0]);
		_custom_putchar('\n');
	}
	return (0);
}
