#include "monty.h"

/**
 * stack_push - add a node at the top of the stack
 * @head: Address of the head of the list
 * @args: List of arguments read from file line
 * @line_number: Number of the line read from
 */
void stack_push(stack_t **head, char **args, unsigned int line_number)
{
	stack_t *new_node;

	if (head == NULL)
		return;

	if (args[1] == NULL || !is_int(args[1]))
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n",
			line_number);
		free_array(args);
		clean_exit(EXIT_FAILURE, *head);
	}

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		free_array(args);
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		clean_exit(EXIT_FAILURE, *head);
	}
	new_node->n = atoi(args[1]);
	new_node->prev = NULL;
	new_node->next = *head;

	if (*head != NULL)
		(*head)->prev = new_node;
	*head = new_node;
}

/**
 * queue_push - add a node to the rear of the queue
 * @head: Head of the list
 * @args: List of arguments read from the file line
 * @line_number: Number of the line read from
 */
void queue_push(stack_t **head, char **args, unsigned int line_number)
{
	stack_t *new_node, *current_node = *head;

	if (head == NULL)
		return;

	if (args[1] == NULL || !is_int(args[1]))
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n",
			line_number);
		free_array(args);
		clean_exit(EXIT_FAILURE, *head);
	}

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		free_array(args);
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		clean_exit(EXIT_FAILURE, *head);
	}
	new_node->n = atoi(args[1]);
	new_node->next = NULL;

	if (current_node == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
		return;
	}

	while (current_node->next != NULL)
		current_node = current_node->next;
	new_node->prev = current_node;
	current_node->next = new_node;
}

/**
 * pall - print all values in the stack
 * @stack: Head of the list
 * @line_number: Number of the line arguments were read from
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	line_number += 1;
	if (*stack == NULL)
		return;

	while (current != NULL)
	{
		printf("%i\n", current->n);
		current = current->next;
	}
}

/**
 * pint - print the first integer in the stack
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	printf("%i\n", (*stack)->n);
}

/**
 * pop - remove the element at the top of the stack
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't pop an empty stack\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	*stack = tmp->next;
	free(tmp);

	if (*stack != NULL)
		(*stack)->prev = NULL;
}
