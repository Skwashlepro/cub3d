/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:57 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 20:22:59 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map(t_data *data)
{
	if (!check_player(data))
		return (printf("Error\n Invalid player position or character\n"), 0);
	if (!checkwalls(data))
		return (0);
	if (!check_closed(data))
		return (printf("Error\n Map is not closed\n"), 0);
	return (1);
}

char	**check_rgb(char *split)
{
	char	**tmp;
	char	*trim;
	int		i;
	int		j;

	i = -1;
	tmp = ft_split(split, ',');
	if (!tmp[2])
		return (free_array(tmp), NULL);
	trim = ft_strtrim(tmp[2], "\n");
	free_str(tmp[2]);
	tmp[2] = ft_strdup(trim);
	free_str(trim);
	while (tmp[++i] && i < 3)
	{
		j = -1;
		while (tmp[i][++j])
			if ((tmp[i][j] < '0' || tmp[i][j] > '9'))
				return (free_array(tmp), NULL);
	}
	return (tmp);
}

void	map_height(char **map, int *height)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	*height = i;
}

char	**copy_map(char **map)
{
	char	**copy;
	int		i;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_array(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
