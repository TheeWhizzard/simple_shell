#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 150

/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 *
 *Description: This program is a basic UNIX command line interpreter that
 *              allows users to enter simple commands and executes them using
 *              fork and exec system calls. It provides a simple shell
 *              interface where users can input commands and see the output.
 *              The program handles command execution, exiting the shell, and
 *              displaying information about command termination.
 *
 * Return: On success, returns 0. On error, returns EXIT_FAILURE.
 */
void execute_command(const char *command)
{
        pid_t pid = fork();

        if (pid == 0)
        {
                if (execvp(command, (char *const *)&command) == -1)
                {
                        perror("Error executing command");
                        exit(EXIT_FAILURE);
                }
        }
        else if (pid > 0)
        {
                int status;

                waitpid(pid, &status, 0);

                if (WIFEXITED(status))
                {
                        printf("Command exited with status: %d\n", WEXITSTATUS(status));
                }
                else if (WIFSIGNALED(status))
                {
                        printf("Command terminated by signal: %d\n", WTERMSIG(status));
                }
        }
        else
        {
                perror("Error forking");
                exit(EXIT_FAILURE);
        }
}
/**
 * main - Entry point
 *
 * char *command: A pointer to a character array
 * size_t len: Stores the length of the input buffer
 * ssize_t read: Stores the return value of the getline function
 * Return: successful program execution 0
 */

int main(void)
{
        char *command = NULL;
        size_t len = 0;
        ssize_t read;

        while (1)
        {
                printf("$ ");
                read = getline(&command, &len, stdin);

                if (read == -1)
                {
                        printf("\nGoodbye!\n");
                        break;
                }

                if (command[read - 1] == '\n')
                {
                        command[read - 1] = '\0';
                }

                if (strcmp(command, "exit") == 0)
                {
                        printf("Goodbye!\n");
                        break;
                }

                execute_command(command);
        }

        free(command);
        return (0);
}

