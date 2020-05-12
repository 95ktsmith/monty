#include "monty.h"

/**
 * free_stack - frees a stack_t list
 * @head: Head of the list
 */
void free_stack(stack_t *head)
{
	if (head == NULL)
		return;

	free_stack(head->next);
	free(head);
}

/**
 * stack_len - stack_t list length
 * @head: Head of the list
 * Return: Number of nodes in the list
 */
int stack_len(stack_t *head)
{
	if (head == NULL)
		return (0);

	return (1 + stack_len(head->next));
}
