#include "shell.h"

/**
 * custom_exit - Exits the shell with a given exit status.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int custom_exit(info_t *info)
{
int exit_status;

if (info->argv[1])
{
exit_status = custom_str_to_int(info->argv[1]);
if (exit_status == -1)
{
info->status = 2;
print_custom_error(info, "Invalid number: ");
custom_puts(info->argv[1]);
custom_putchar('\n');
return (1);
}
info->error_num = custom_str_to_int(info->argv[1]);
return (-2);
}
info->error_num = -1;
return (-2);
}

/**
 * custom_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int custom_cd(info_t *info)
{
char *current_dir, *target_dir, buffer[1024];
int chdir_ret;

current_dir = custom_getcwd(buffer, 1024);
if (!current_dir)
custom_puts("TODO: >>getcwd failure message here<<\n");

if (!info->argv[1])
{
target_dir = custom_getenv(info, "HOME=");
if (!target_dir)
chdir_ret = /* TODO: Define the desired behavior */;
else
chdir_ret = chdir(target_dir);
}
else if (custom_strcmp(info->argv[1], "-") == 0)
{
if (!custom_getenv(info, "OLDPWD="))
{
custom_puts(current_dir);
custom_putchar('\n');
return (1);
}
custom_puts(custom_getenv(info, "OLDPWD="));
custom_putchar('\n');
chdir_ret = /* TODO: Define the desired behavior */;
}
else
chdir_ret = chdir(info->argv[1]);

if (chdir_ret == -1)
{
print_custom_error(info, "Unable to change directory to ");
custom_puts(info->argv[1]);
custom_putchar('\n');
}
else
{
custom_setenv(info, "OLDPWD", custom_getenv(info, "PWD="));
custom_setenv(info, "PWD", custom_getcwd(buffer, 1024));
}
return (0);
}

/**
 * custom_help - Prints help information.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int custom_help(info_t *info)
{
char **arg_array;

arg_array = info->argv;
custom_puts("Help: Functionality not implemented yet.\n");
if (0)
custom_puts(*arg_array);
return (0);
}

