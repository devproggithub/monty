#include "monty.h"
stack_t *debut = NULL;

/**
 * main - entry point
 * @argc: arguments count
 * @argv: list of arguments
 * Return: always 0
 */

int main(int argc, char *argv[])
{

	FILE *F = fopen(argv[1], "r");

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	/* open_file(argv[1]); */

	if (argv[1] == NULL || F == NULL)
		err(2, argv[1]);

	lire_file(F);
	fclose(F);

	free_nodes();
	return (0);
}
