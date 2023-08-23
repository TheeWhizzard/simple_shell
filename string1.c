#include "shell.h"

/**
 * _strcpy - Copies string
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: A pointer to the destination buffer
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: The pointer to a duplicated string, or NULL on failure
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (str[length])
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
		return (NULL);

	for (int i = 0; i <= length; i++)
		ret[i] = str[i];

	return (ret);
}

/**
 * _puts - Prints string to stdout
 * @str: String to print
 *
 * Return: None
 */
void _puts(const char *str)
{
	int i = 0;

	if (str == NULL)
		return;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes a character to stdout
 * @c: Character to write
 *
 * Return: Success 1.Error, -1 is returned.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

