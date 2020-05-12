#ifndef MONTY_H
#define MONTY_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern FILE *file_stream;

/* In main.c */
void clean_exit(int status, stack_t *stack);
void perform_op(char **args, stack_t **stack, unsigned int line, int *mode);
void (*get_op_func(char *op_code))(stack_t **stack, unsigned int line_number);

/* In _strtok.c */
char **_strtok(char *str, stack_t *stack);
int token_count(char *str);
void free_array(char **tokens);

/* In list_functions.c */
void free_stack(stack_t *head);
int stack_len(stack_t *head);

/* ops_1.c */
void stack_push(stack_t **head, char **args, unsigned int line_number);
void queue_push(stack_t **head, char **args, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);

#endif /* MONTY_H */
