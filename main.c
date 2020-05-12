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
	unsigned int line_number = 1, buffer_size = 1024;
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

	while (fgets(buffer, buffer_size, file_stream))
	{
		if (buffer[0] == '#')
			continue;
		args = _strtok(buffer, stack);
		if (args == NULL)
			continue;

		perform_op(args, &stack, line_number, &stack_mode);
		free_array(args);
		line_number++;
	}
	fclose(file_stream);
	free_stack(stack);
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
	if (strcmp(args[0], "push") == 0 && *mode == 1)
		stack_push(stack, args, line);
	else if (strcmp(args[0], "push") == 0 && *mode == 0)
		queue_push(stack, args, line);
	else if (strcmp(args[0], "stack") == 0 && *mode == 0)
		*mode = 1;
	else if (strcmp(args[0], "queue") == 0 && *mode == 1)
		*mode = 0;
	else
	{
		if (get_op_func(args[0]) == NULL)
		{
			dprintf(STDERR_FILENO, "L%u: unkown instruction %s\n",
				line, args[0]);
			free_array(args);
			clean_exit(EXIT_FAILURE, *stack);
		}
		else
			get_op_func(args[0])(stack, line);
	}

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
		{NULL, NULL}
	};

	while (funcs[index].opcode != NULL)
	{
		if (strcmp(funcs[index].opcode, op_code) == 0)
			return (*(funcs + index)->f);
	}

	return (NULL);
}
