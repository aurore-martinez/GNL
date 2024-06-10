/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:31:14 by aumartin          #+#    #+#             */
/*   Updated: 2024/06/10 12:53:53 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* Structure */
typedef struct s_gnl
{
	char			*stored_line;
	struct s_gnl	*next;
}	t_gnl;

/* Functions get_next_line */
t_gnl	*get_gnl_data(t_gnl **gnl_list);
void	remove_gnl_data(t_gnl **gnl_list);
char	*get_next_line(int fd);
char	*read_and_store(int *end_of_line, int fd, char *stored_line);
char	*extract_line(int *eol, char *stored_line, char *line_to_return);

/* Functions get_next_line_utils */
char	*gnl_calloc(size_t size);
char	*gnl_cat(char *current_line, char *buffer);
int		gnl_strlen(char *s);
int		gnl_find_newline(char *s);
char	*gnl_memmove(char *current_line);

#endif
