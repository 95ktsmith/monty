#include "monty.h"

/**
 * mod - diviedes the second node by the top node and stores the remainder
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void mod(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || stack_len(*stack) < 2)
	{
		dprintf(STDERR_FILENO, "L%u: can't mod, stack too short\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	if ((*stack)->n == 0)
	{
		dprintf(STDERR_FILENO, "L%u: division by zero\n", line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	*stack = (*stack)->next;
	(*stack)->n %= (*stack)->prev->n;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * pchar - prints the char at the top of the stack
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: can't pchar, stack empty\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}

	if ((*stack)->n >= ' ' && (*stack)->n <= '~')
		printf("%c\n", (*stack)->n);
	else
	{
		dprintf(STDERR_FILENO, "L%u: can't pchar, value out of range\n",
			line_number);
		clean_exit(EXIT_FAILURE, *stack);
	}
}

/**
 * pstr - prints the string starting at the top of the stack
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	line_number++;
	while (tmp)
	{
		if (tmp->n < ' ' || tmp->n > '~')
			break;
		printf("%c", tmp->n);
		tmp = tmp->next;
	}
	printf("\n");
}

/**
 * rotr - Move bottom element to the top of the stack
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack, *end = *stack;

	line_number++;
	if (*stack == NULL || stack_len(*stack) < 2)
		return;

	while (end->next)
		end = end->next;

	end->prev->next = NULL;
	end->next = top;
	end->prev = NULL;
	top->prev = end;
	*stack = end;
}

/**
 * rotl - Move top element to the bottom of the stack
 * @stack: Head of the stack
 * @line_number: Number of the line the arguments were read from
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack, *end = *stack;

	line_number++;
	if (*stack == NULL || stack_len(*stack) < 2)
		return;

	while (end->next)
		end = end->next;

	*stack = top->next;
	top->next->prev = NULL;
	top->prev = end;
	top->next = NULL;
	end->next = top;
}