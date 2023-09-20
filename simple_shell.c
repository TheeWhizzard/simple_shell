#include "shell.h"

/**
 * main - Simple Shell
 *
 * Description:
 * This is a basic implementation of a shell in C. It can execute single-word
 * commands and display a prompt for each command. It handles errors and the
 * "end of file" condition (Ctrl+D).
 *
 * Usage:
 * Compile the program and run it.
 * Type "exit" to quit the shell.
 */
#define MAX_INPUT_LENGTH 100

int main(void)
{
	char input[MAX_INPUT_LENGTH];
	pid_t pid;

	while (1)
	{
		printf("simple_shell> ");
		fflush(stdout);

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strlen(input) - 1] = '\0';

		pid = fork();

		if (pid == 0)
		{
			if (execlp(input, input, (char *)NULL) == -1)
			{
				perror("Command not found");
				exit(1);
			}
		}
		else if (pid < 0)
		{
			perror("Forking error");
		}
		else
		{
			int status;

			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
