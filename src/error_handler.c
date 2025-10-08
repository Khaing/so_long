/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:11:13 by kmar              #+#    #+#             */
/*   Updated: 2025/10/07 12:11:18 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_error(char *message)
{
	write(STDOUT_FILENO, ERROR_MSG, strlen(ERROR_MSG));
	if (message)
	{
		write(STDOUT_FILENO, message, strlen(message));
		write(STDOUT_FILENO, "\n", 1);
	}
}
