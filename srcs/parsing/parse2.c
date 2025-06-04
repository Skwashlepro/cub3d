/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:03:15 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/06/04 19:28:18 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_map(t_data *data, char *str)
{
	char	*tmp;

    tmp = NULL;
	if (!check_extension(str))
	{
		printf("Error\n Wrong extension\n");
		return (0);
	}
	data->fd = open(str, O_RDONLY);
	if (data->fd == -1)
		return (printf("Error\nFile not found\n"), 2);
	data->map = getmap(data, data->fd, data->map, tmp);
	if (!data->map)
		return (close(data->fd), 0);
	close(data->fd);
	return (1);
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	check_player(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				player_count++;
				data->p1.player_x = j;
				data->p1.player_y = i;
				data->p1.player_dir = data->map[i][j];
			}
			else if (!is_valid_char(data->map[i][j]))
				return (0);
		}
	}
	return (player_count == 1);
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
			free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	valid_map(t_data *data)
{
	if (!checkwalls(data))
		return (0);
	if (!check_player(data))
		return (printf("Error\n Invalid player position or character\n"), 0);
	if (!check_closed(data))
		return (printf("Error\n Map is not closed\n"), 0);
	return (1);
}