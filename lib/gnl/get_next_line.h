/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:45:38 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 20:17:45 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}						t_list;

char				*get_next_line(int fd, int to_free);
void				reader(int fd, t_list **stsh, int *i);
void				stasher(t_list **stsh, char *buf, int i);
void				keep_line(t_list *stsh, char **line);
void				make_line(char **line, t_list *stsh);
void				free_stsh(t_list *stsh);
int					eol(t_list *stsh);
void				clear_stsh(t_list **stsh);
t_list				*last_elem(t_list *stsh);

#endif
