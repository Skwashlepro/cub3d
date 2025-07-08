/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:48:20 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/07/08 18:02:05 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	floodfill(t_data *data, int x, int y, char **map)
{
	if (y < 0 || x < 0 || y >= data->map_height || x >= data->map_width
		|| map[y][x] == ' ')
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	floodfill(data, x + 1, y, map);
	floodfill(data, x - 1, y, map);
	floodfill(data, x, y + 1, map);
	floodfill(data, x, y - 1, map);
}

int	check_closed(t_data *data)
{
	char	**map_copy;

	map_copy = copy_map(data->map);
	if (!map_copy)
		return (0);
	floodfill(data, (int)data->p1.pos_x, (int)data->p1.pos_y, map_copy);
	free_array(map_copy);
	return (1);
}

static int	check_surrounding_cells(t_data *data, int i, int j, int row_len)
{
	if (i == 0 || j == 0 || i == data->map_height - 1 || j == row_len - 1)
		return (printf("Error: Map not closed at boundary [%d][%d]\n", i, j),
			0);
	if (data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' '
		|| data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
		return (printf("Error: Map not closed at [%d][%d]\n", i, j), 0);
	return (1);
}

int	checkwalls(t_data *data)
{
	int	i;
	int	j;
	int	row_len;

	map_height(data->map, &data->map_height);
	data->map_width = ft_strlen(data->map[0]);
	i = -1;
	while (++i < data->map_height)
	{
		row_len = ft_strlen(data->map[i]);
		j = -1;
		while (++j < row_len)
		{
			if (data->map[i][j] == '0' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'E'
				|| data->map[i][j] == 'W')
			{
				if (!check_surrounding_cells(data, i, j, row_len))
					return (0);
			}
		}
	}
	return (1);
}

char	**getmap(t_data *data, int fd, char **map, char *tmp)
{
	while (fd)
	{
		data->line = get_next_line(fd);
		if (!data->line)
		{
			if (!data->buffer)
				return (printf("Error\nempty file\n"), NULL);
			break ;
		}
		if (!data->buffer)
			data->buffer = ft_strdup2("");
		tmp = data->buffer;
		data->buffer = ft_strjoin2(tmp, data->line);
		free_db(tmp, data->line);
	}
	if (data->error == 1)
		return (free_str(data->buffer), NULL);
	map = ft_split(data->buffer, '\n');
	if (!map)
		return (free_str(data->buffer), NULL);
	map_height(map, &data->map_height);
	return (free_str(data->buffer), map);
}
