/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:26:34 by aumartin          #+#    #+#             */
/*   Updated: 2024/06/05 14:01:29 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	0
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* Functions get_next_line */
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
