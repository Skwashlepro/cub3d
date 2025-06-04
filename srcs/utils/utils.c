/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:44:35 by luctan            #+#    #+#             */
/*   Updated: 2025/06/04 18:58:53 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return ;
}

void	free_db(char *str, char *str2)
{
	free(str);
	free(str2);
	return ;
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s2;

	s2 = (char *)s;
	i = ft_strlen(s);
	if (c == '\0')
		return (&s2[i]);
	i = 0;
	while (s2[i])
	{
		if (s2[i] == (char)c)
			return (&s2[i]);
		i++;
	}
	return (NULL);
}

int	check_extension(char *fichier)
{
	char	*ext;

	ext = ft_strchr(fichier, '.');
	if (ext != NULL && ft_strcmp(ext, ".cub") == 0)
		return (1);
	ft_printf("Error\nWrong ext\n");
	return (0);
}
