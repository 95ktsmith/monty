#include "monty.h"

FILE *file_stream = NULL;

/**
 * main - entry point
 * Description: Interprets and executes monty code from a file
 * @argc: Number of arguments
 * @argv: List of arguments
 * Return: 0 if successful, -1 if not.
 */
int main(int argc, char *argv[])
{
	unsigned int line_number = 0;
	int stack_mode = 1;
	char buffer[1024];
	char **args;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file_stream = fopen(argv[1], "r");
	if (file_stream == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(buffer, 1024, file_stream))
	{
		line_number++;
		args = _strtok(buffer, stack);
		if (args == NULL)
			continue;
		if (args[0][0] == '#')
		{
			free_array(args);
			continue;
		}
		perform_op(args, &stack, line_number, &stack_mode);
	}
	fclose(file_stream);
	free_stack(stack);
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * clean_exit - frees the stack, closes file, exits
 * @stack: Head of the stack
 * @status: Status to use when exiting
 */
void clean_exit(int status, stack_t *stack)
{
	free_stack(stack);
	fclose(file_stream);
	exit(status);
}

/**
 * perform_op - perform operator function
 * Description: Tries to find a match between the first token of the
 *              args list and one of the available functions, and executes
 *              it if a match is found. If no match is found, an error is
 *              printed and the program exits.
 * @args: List of arguments
 * @stack: Address of the head of the stack
 * @line: Number of the line the arguments were read from
 * @mode: Current behavior mode of the program. 1 for stack, 0 for queue.
 */
void perform_op(char **args, stack_t **stack, unsigned int line, int *mode)
{
	void (*func_ptr)(stack_t **stack, unsigned int line_number);

	if (strcmp(args[0], "push") == 0 && *mode == 1)
		stack_push(stack, args, line);
	else if (strcmp(args[0], "push") == 0 && *mode == 0)
		queue_push(stack, args, line);
	else if (strcmp(args[0], "stack") == 0 && *mode == 0)
		*mode = 1;
	else if (strcmp(args[0], "queue") == 0 && *mode == 1)
		*mode = 0;
	else if (strcmp(args[0], "nop") != 0)
	{
		func_ptr = get_op_func(args[0]);
		if (func_ptr == NULL)
		{
			dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n",
				line, args[0]);
			free_array(args);
			clean_exit(EXIT_FAILURE, *stack);
		}
		else
		{
			free_array(args);
			func_ptr(stack, line);
			return;
		}
	}
	free_array(args);
}

/**
 * get_op_func - get operator function
 * @op_code: Name of the operator to look for
 * Return: A pointer to the function if a match is found, or NULL if no match.
 */
void (*get_op_func(char *op_code))(stack_t **stack, unsigned int line_number)
{
	int index = 0;
	instruction_t funcs[] = {
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"sub", sub},
		{"mul", mul},
		{"div", divide},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	while (funcs[index].opcode != NULL)
	{
		if (strcmp(funcs[index].opcode, op_code) == 0)
			return (*(funcs + index)->f);
		index++;
	}
	return (NULL);
}

/**
 * is_int - checks if a string has only numerical characters
 * @str: String to check
 * Return: 1 if the string contains only numerical characters, or has a leading
 *         sign, and 0 if it contains any other characters.
 */
int is_int(char *str)
{
	int index = 0;

	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
		{
			if (index != 0 || str[index] != '-')
				return (0);
		}
		index++;
	}
	return (1);
}
