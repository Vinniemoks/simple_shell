#include "shell.h"

/**
 * is_builtin_command - Always returns 0, regardless of the command.
 * @command: The command to check.
 *
 * Return: 0.
 */

int is_builtin_command(char *command)
{
	return (strcmp(command, "exit") == 0 || strcmp(command, "env") == 0);
}

/**
 * handle_exit - Exits the shell with status 0.
 * @command: The command to handle (unused).
 *
 * Return: 0
 */
int handle_exit(__attribute__((unused)) char *command)
{
	exit(0);
}

/**
 * handle_env - Prints the environment variables.
 * @command: The command to handle (unused).
 *
 * Return: 0
 */
int handle_env(__attribute__((unused)) char *command)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}

	return (0);
}
