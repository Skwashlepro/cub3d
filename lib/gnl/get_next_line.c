/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:37:34 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 20:18:50 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd, int to_free)
{
	static t_list	*stsh;
	char			*l;
	int				i;

	if (to_free == 1)
		return (free_stsh(stsh), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 1;
	l = NULL;
	reader(fd, &stsh, &i);
	if (!stsh)
		return (NULL);
	keep_line(stsh, &l);
	clear_stsh(&stsh);
	if (l[0] == '\0')
	{
		free_stsh(stsh);
		stsh = NULL;
		free(l);
		return (NULL);
	}
	return (l);
}

void	reader(int fd, t_list **stsh, int *i)
{
	char	*buf;

	while (!(eol(*stsh)) && *i)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return ;
		*i = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stsh == NULL && *i == 0) || *i == -1)
		{
			free(buf);
			return ;
		}
		buf[*i] = '\0';
		stasher(stsh, buf, *i);
		free(buf);
	}
}

void	stasher(t_list **stsh, char *buf, int i)
{
	t_list	*c;
	t_list	*new;
	int		j;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (i + 1));
	if (new->content == NULL)
		return ;
	j = 0;
	while (buf[j] && j < i)
	{
		new->content[j] = buf[j];
		j++;
	}
	new->content[j] = '\0';
	if (!*stsh)
	{
		*stsh = new;
		return ;
	}
	c = last_elem(*stsh);
	c->next = new;
}

void	keep_line(t_list *stsh, char **line)
{
	int	i;
	int	j;

	if (stsh == NULL)
		return ;
	make_line(line, stsh);
	if (*line == NULL)
		return ;
	j = 0;
	while (stsh)
	{
		i = 0;
		while (stsh->content[i])
		{
			if (stsh->content[i] == '\n')
			{
				(*line)[j++] = stsh->content[i];
				break ;
			}
			(*line)[j++] = stsh->content[i++];
		}
		stsh = stsh->next;
	}
	(*line)[j] = '\0';
}

void	clear_stsh(t_list **stsh)
{
	t_list	*lst;
	t_list	*clean;
	int		i;
	int		j;

	clean = malloc(sizeof(t_list));
	if (!stsh || !clean)
		return ;
	clean->next = NULL;
	lst = last_elem(*stsh);
	i = 0;
	while (lst->content[i] && lst->content[i] != '\n')
		i++;
	if (lst->content && lst->content[i] == '\n')
		i++;
	clean->content = malloc(sizeof(char)
			* ((int)ft_strlen(lst->content) - i) + 1);
	if (clean->content == NULL)
		return ;
	j = 0;
	while (lst->content[i])
		clean->content[j++] = lst->content[i++];
	clean->content[j] = '\0';
	free_stsh(*stsh);
	*stsh = clean;
}
