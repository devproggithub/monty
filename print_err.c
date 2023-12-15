#include "monty.h"

/**
 * err - Imprime les messages d'erreur appropriés déterminés par leur code d'erreur.
 * @error_code: Les codes d'erreur sont les suivants :
 * (1) => L'utilisateur ne donne aucun fichier ou plus d'un fichier au programme.
 * (2) => Le fichier fourni n'est pas un fichier pouvant être ouvert ou lu.
 * (3) => Le fichier fourni contient une instruction invalide.
 * (4) => Lorsque le programme ne parvient pas à allouer plus de mémoire.
 * (5) => Lorsque le paramètre passé à l'instruction "push" n'est pas un int.
 * (6) => Lorsque la pile est vide pour une pinte.
 * (7) => Lorsque la pile est vide pour pop.
 * (8) => Lorsque la pile est trop courte pour fonctionner.
 */
void err(int error_code, ...)
{
	va_list ag;
	char *op;
	int l_num;

	va_start(ag, error_code);
	switch (error_code)
	{
		case 1:
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 2:
			fprintf(stderr, "Error: Can't open file %s\n",
				va_arg(ag, char *));
			break;
		case 3:
			l_num = va_arg(ag, int);
			op = va_arg(ag, char *);
			fprintf(stderr, "L%d: unknown instruction %s\n", l_num, op);
			break;
		case 4:
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			fprintf(stderr, "L%d: usage: push integer\n", va_arg(ag, int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * more_err - gère les erreurs.
 * @error_code: Les codes d'erreur sont les suivants :
 * (6) => Lorsque la pile est vide pour une pinte.
 * (7) => Lorsque la pile est vide pour pop.
 * (8) => Lorsque la pile est trop courte pour fonctionner.
 * (9) => Division par zéro.
 */
void more_err(int error_code, ...)
{
	va_list ag;
	char *op;
	int l_num;

	va_start(ag, error_code);
	switch (error_code)
	{
		case 6:
			fprintf(stderr, "L%d: can't pint, stack empty\n",
				va_arg(ag, int));
			break;
		case 7:
			fprintf(stderr, "L%d: can't pop an empty stack\n",
				va_arg(ag, int));
			break;
		case 8:
			l_num = va_arg(ag, unsigned int);
			op = va_arg(ag, char *);
			fprintf(stderr, "L%d: can't %s, stack too short\n", l_num, op);
			break;
		case 9:
			fprintf(stderr, "L%d: division by zero\n",
				va_arg(ag, unsigned int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * string_err - gère les erreurs.
 * @error_code: Les codes d'erreur sont les suivants :
 * (10) => Le nombre à l'intérieur d'un nœud est en dehors des limites ASCII.
 * (11) => La pile est vide.
 */
void string_err(int error_code, ...)
{
	va_list ag;
	int l_num;

	va_start(ag, error_code);
	l_num = va_arg(ag, int);
	switch (error_code)
	{
		case 10:
			fprintf(stderr, "L%d: can't pchar, value out of range\n", l_num);
			break;
		case 11:
			fprintf(stderr, "L%d: can't pchar, stack empty\n", l_num);
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}
