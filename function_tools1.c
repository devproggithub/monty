#include "monty.h"

/**
 * lire_file - lit un fichier
 * @F: pointeur vers le descripteur de fichier
 * Retour : void
 */
void lire_file(FILE *F)
{
	int line_n, format = 0;
	char *buff = NULL;
	size_t len = 0;

	for (line_n = 1; getline(&buff, &len, F) != -1; line_n++)
	{
		format = separe_line(buff, line_n, format);
	}
	free(buff);
}

/**
 * separe_line - Sépare chaque ligne en jetons pour déterminer
 * quelle fonction appeler
 * @buff: ligne du fichier
 * @line_n: numéro de ligne
 * @format: format de stockage. Si 0, les nœuds seront entrés sous forme de pile.
 * si 1 nœuds seront entrés en file d'attente.
 * Return : renvoie 0 si l'opcode est stack. 1 si file d'attente.
 */

int separe_line(char *buff, int line_n, int format)
{
	char *opcode, *val;
	const char *del_im = "\n ";

	if (buff == NULL)
		err(4);

	opcode = strtok(buff, del_im);
	if (opcode == NULL)
		return (format);
	val = strtok(NULL, del_im);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	trouve_func(opcode, val, line_n, format);
	return (format);
}


/**
 * trouve_func - trouve la fonction appropriée pour l'opcode
 * @opcode: opcode
 * @val: argument de l'opcode
 * @format: format de stockage. Si 0, les nœuds seront entrés sous forme de pile.
 * @ln: numéro de ligne
 * si 1 nœuds seront entrés en file d'attente.
 * Retour : void
 */

void trouve_func(char *opcode, char *val, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			appel_func(func_list[i].f, opcode, val, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}

/**
 * appel_func - Appelle la fonction requise.
 * @func: Pointeur vers la fonction qui est sur le point d'être appelée.
 * @op: chaîne représentant l'opcode.
 * @val: chaîne représentant une valeur numérique.
 * @ln: numéro de ligne de l'instruction.
 * @format: spécificateur de format. Si 0, les nœuds seront entrés sous forme de pile.
 * si 1 nœuds seront entrés en file d'attente.
 */

void appel_func(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&debut, ln);
}


/**
 * free_nodes - Frees nodes in the stack.
 */
void free_nodes(void)
{
	stack_t *tmp;

	if (debut == NULL)
		return;

	while (debut != NULL)
	{
		tmp = debut;
		debut = debut->next;
		free(tmp);
	}
}
