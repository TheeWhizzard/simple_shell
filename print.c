#include <stdio.h>

/**
 * print_message - Prints a message 5 times
 */
void print_message(void)
{
    int i;

    for (i = 0; i < 5; i++)
    {
	    printf("Hello, Betty!\n");
    }
}

/**
 * main - Entry point of the program
 * Return: 0 (success)
 */
int main(void)
{
    print_message();
    return (0);
}

