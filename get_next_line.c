/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:26:38 by aumartin          #+#    #+#             */
/*   Updated: 2024/06/10 14:03:31 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*stored_line;
	char		*line_to_return;
	int			end_of_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	line_to_return = NULL;
	end_of_line = -1;
	stored_line = read_and_store(&end_of_line, fd, stored_line);
	printf("stored_line :%s\n", stored_line);
	if (!stored_line)
		return (NULL);
	line_to_return = extract_line(&end_of_line, stored_line, line_to_return);
	printf("line_to_return : %s\n", line_to_return);
	if (!line_to_return)
		return (NULL);
	stored_line = gnl_memmove(stored_line);
	printf("stored_line aps memmove :%s\n", stored_line);
	if (stored_line && *stored_line == '\0')
	{
		free(stored_line);
		stored_line = NULL;
	}
	return (line_to_return);
}

char	*read_and_store(int *end_of_line, int fd, char *stored_line)
{
	char	*buffer;
	int		rd;

	buffer = gnl_calloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stored_line), NULL);
	rd = 1;
	while (*end_of_line == -1 && rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (free(stored_line), free(buffer), NULL);
		buffer[rd] = '\0';
		if (rd > 0)
		{
			stored_line = gnl_cat(stored_line, buffer);
		}
		*end_of_line = gnl_find_newline(stored_line);
	}
	free(buffer);
	return (stored_line);
}

char	*extract_line(int *eol, char *stored_line, char *line_to_return)
{
	int		i;

	if (!stored_line)
		return (NULL);
	line_to_return = gnl_calloc(gnl_strlen(stored_line) + 1);
	if (!line_to_return)
		return (NULL);
	i = 0;
	while (*(stored_line + i) && *(stored_line + i) != '\n')
	{
		*(line_to_return + i) = *(stored_line + i);
		i++;
	}
	if (*(stored_line + i) == '\n')
	{
		*(line_to_return + i++) = '\n';
		*eol = i;
	}
	*(line_to_return + i) = '\0';
	return (line_to_return);
}
