/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:26:38 by aumartin          #+#    #+#             */
/*   Updated: 2024/06/05 16:18:34 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
get_next_line : Gère le fd et appelle les fonctions pour lire et traiter la ligne.
read_and_store : Lit des données du fichier et les stocke dans stored_line jusqu'à ce qu'une nouvelle ligne soit trouvée ou que le fichier soit complètement lu.
extract_line : Crée une nouvelle chaîne contenant la ligne jusqu'à la fin de ligne (ou la fin du fichier) et met à jour la position de fin de ligne (end_of_line_position).
*/

#include "get_next_line.h"
#include <stdio.h>

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
	if (!stored_line)
		return (NULL);
	line_to_return = extract_line(&end_of_line, stored_line, line_to_return);
	if (!line_to_return)
		return (NULL);
	stored_line = gnl_memmove(stored_line);
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
	{
		free(stored_line);
		return (NULL);
	}
	rd = 1;
	while (*end_of_line == -1 && rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		//printf("buffer: %s\n", buffer);
		//printf("stored_line: %s\n", stored_line);
		if (rd == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		if (rd > 0)
		{
			stored_line = gnl_cat(stored_line, buffer);
			//printf("After gnl_cat: %s\n", stored_line);
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
		*eol = i + 1;
	}
	*(line_to_return + i + 1) = '\0';
	//printf("Extracted line: %s\n", line_to_return);
	return (line_to_return);
}
