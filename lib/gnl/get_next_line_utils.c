/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:42 by luctan            #+#    #+#             */
/*   Updated: 2025/05/22 03:02:03 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	eol(t_list *stsh)
{
	int		i;
	t_list	*c;

	if (stsh == NULL)
		return (0);
	c = last_elem(stsh);
	i = 0;
	while (c->content[i])
	{
		if (c->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*last_elem(t_list *stsh)
{
	t_list	*c;

	c = stsh;
	while (c && c->next)
		c = c->next;
	return (c);
}

void	make_line(char **line, t_list *stsh)
{
	int	i;
	int	len;

	len = 0;
	while (stsh)
	{
		i = 0;
		while (stsh->content[i])
		{
			if (stsh->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stsh = stsh->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_stsh(t_list *stsh)
{
	t_list	*c;
	t_list	*next;

	c = stsh;
	while (c)
	{
		free(c->content);
		next = c->next;
		free(c);
		c = next;
	}
}

