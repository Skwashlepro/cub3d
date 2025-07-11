/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:57 by luctan            #+#    #+#             */
/*   Updated: 2025/07/11 19:42:30 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map(t_data *data)
{
	if (!check_player(data))
		return (printf("Error\n Invalid player position or character\n"), 0);
	normalize_map(data);
	if (!checkwalls(data))
		return (0);
	if (!check_closed(data))
		return (printf("Error\n Map is not closed\n"), 0);
	return (1);
}

int	check_comma(char *str)
{
	int	i;
	int	comma_count;

	i = -1;
	comma_count = 0;
	while (str[++i])
		if (str[i] == ',')
			comma_count++;
	return (comma_count);
}

char	**check_rgb(char *split)
{
	char	**tmp;
	char	*trim;
	int		i;
	int		j;

	i = -1;
	if (check_comma(split) != 2)
		return (printf("Error\n Invalid RGB format\n"), NULL);
	tmp = ft_split(split, ',');
	while (tmp[++i])
		if (i > 2)
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
		printf("tmp[%d] = %s\n", i, tmp[i]);
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
			return (free_array(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
