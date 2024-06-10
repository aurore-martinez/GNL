/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line_bonus.c							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aumartin <aumartin@42.fr>				  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/07 11:45:28 by aumartin		  #+#	#+#			 */
/*   Updated: 2024/06/10 11:08:56 by aumartin		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

/* static t_gnl	*get_gnl_data(t_gnl **gnl_list) */

#include "get_next_line_bonus.h"

t_gnl	*get_gnl_data(t_gnl **gnl_list)
{
	t_gnl	*current;
	t_gnl	*prev;

	current = *gnl_list;
	prev = NULL;
	while (current)
	{
		prev = current;
		current = current->next;
	}
	current = (t_gnl *)malloc(sizeof(t_gnl));
	if (!current)
		return (NULL);
	current->stored_line = NULL;
	current->next = NULL;
	if (prev)
		prev->next = current;
	else
		*gnl_list = current;
	return (current);
}

//first node never freed
void	remove_gnl_data(t_gnl **gnl_list)
{
	t_gnl	*current;
	t_gnl	*prev;

	current = *gnl_list;
	prev = NULL;
	while (current)
	{
		prev = current;
		current = current->next;
		free(current->stored_line); //current may be null
	 	free(current);
	}
	*gnl_list = NULL;
}

char	*get_next_line(int fd)
{
	static t_gnl	*gnl_list;
	t_gnl			*gnl_data;
	char			*line_to_return;
	int				eol;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl_data = get_gnl_data(&gnl_list);
	if (!gnl_data)
		return (NULL);
	line_to_return = NULL;
	eol = -1;
	gnl_data->stored_line = read_and_store(&eol, fd, gnl_data->stored_line);
	if (!gnl_data->stored_line)
		return (remove_gnl_data(&gnl_list), NULL);
	line_to_return = extract_line(&eol, gnl_data->stored_line, line_to_return);
	if (!line_to_return)
		return (remove_gnl_data(&gnl_list), NULL);
	gnl_data->stored_line = gnl_memmove(gnl_data->stored_line);
	if (gnl_data->stored_line && *gnl_data->stored_line == '\0')
	{
		free(gnl_data->stored_line);
		gnl_data->stored_line = NULL;
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
