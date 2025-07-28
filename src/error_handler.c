#include "../includes/so_long.h"

void	print_error(char *message)
{
	write(STDERR_FILENO, ERROR_MSG, strlen(ERROR_MSG));
	if (message)
	{
		write(STDERR_FILENO, message, strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
}