/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:48:20 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/06/11 18:45:53 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	floodfill(t_data *data, int x, int y, char **map)
{
	printf("Floodfill at (%d, %d)\n", x, y);
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

static int	error_map(char *buffer)
{
	int	i;

	if (buffer[0] == '\n')
		return (1);
	i = 1;
	while (buffer[i] != '\0')
	{
		if (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i - 1] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_closed(t_data *data)
{
	int		i;
	int		ss;
	// int		j;
	char	**map_copy;

	ss = 0;
	i = 0;
	map_copy = copy_map(data->map);
	if (!map_copy)
		return (0);
	floodfill(data, data->p1.pos_x - 0.5, data->p1.pos_y - 0.5, map_copy);
	while (map_copy[ss])
		printf("%s\n", map_copy[ss++]);
	// while (map_copy[i])
	// {
	// 	j = 0;
	// 	while (map_copy[i][j])
	// 	{
	// 		if (map_copy[i][j] == '0')
	// 		{
	// 			return (free_map(map_copy), 0);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	free_map(map_copy);
	return (1);
}

// int	checkwalls(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = ft_strlen(data->map[0]);
// 	data->map_width = i;
// 	j = 0;
// 	while (data->map[j])
// 	{
// 		if (j == 0 || j == data->map_width - 1)
// 		{

// 		}
// 		// else if(data->map[j][0] != '1' || data->map[j][i - 1] != '1')
// 		// 	return (printf("Erreur2\n"), 0);
// 		j++;
// 	}
// 	return (1);
// }

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

void	map_height(char **map, int *height)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	*height = i;
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
		if (error_map(data->line) == 1)
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
