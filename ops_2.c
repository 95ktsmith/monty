#include "monty.h"

/**
 * swap - swaps the top two elements of the stack
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (stack == NULL || stack_len(*stack) < 2)
	{
		dprintf(STDERR_FILENO, "L%u: can't swap, stack too short\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	tmp = *stack;
	*stack = tmp->next;
	tmp->prev = (*stack);
	tmp->next = (*stack)->next;
	(*stack)->prev = NULL;
	(*stack)->next = tmp;
	if((*stack)->next != NULL)
		(*stack)->next->prev = tmp;
}

/**
 * add - Adds the top two elements of the stack together
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack, *tmp_next;

	if (stack == NULL || stack_len(*stack) < 2)
	{
		dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	tmp_next = tmp->next;
	tmp_next->n += tmp->n;
	free(tmp);
	tmp_next->prev = NULL;
	*stack = tmp_next;
}

/**
 * sub - Subtracts the top node from the second node
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void sub(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || stack_len(*stack) < 2)
	{
		dprintf(STDERR_FILENO, "L%u: can't sub, stack too short\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	*stack = (*stack)->next;
	(*stack)->n -= (*stack)->prev->n;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * mul - Multiplies the top node by the second node
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void mul(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || stack_len(*stack) < 2)
	{
		dprintf(STDERR_FILENO, "L%u: can't mul, stack too short\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	*stack = (*stack)->next;
	(*stack)->n *= (*stack)->prev->n;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * divide - divides the second node by the top node
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void divide(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || stack_len(*stack) < 2)
	{
		dprintf(STDERR_FILENO, "L%u: can't mul, stack too short\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	if ((*stack)->n == 0)
	{
		dprintf(STDERR_FILENO, "L%u: division by zero\n", line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	*stack = (*stack)->next;
	(*stack)->n = (*stack)->n / (*stack)->prev->n;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
