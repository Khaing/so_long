/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmar <kmar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by kmar              #+#    #+#             */
/*   Updated: 2025/10/08 00:00:00 by kmar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	*read_line_buffer(int fd, char *buffer)
{
	char	c;
	int		i;
	int		ret;

	i = 0;
	ret = read(fd, &c, 1);
	while (ret && c != '\n' && i < 9999)
	{
		if (c != '\r')
			buffer[i++] = c;
		ret = read(fd, &c, 1);
	}
	if (ret == 0 && i == 0)
		return (NULL);
	buffer[i] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;

	buffer = malloc(10000);
	if (!buffer)
		return (NULL);
	if (!read_line_buffer(fd, buffer))
	{
		free(buffer);
		return (NULL);
	}
	line = malloc(strlen(buffer) + 1);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	strcpy(line, buffer);
	free(buffer);
	return (line);
}

int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}
