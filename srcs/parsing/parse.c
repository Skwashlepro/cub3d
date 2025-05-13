/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:48:20 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/05/13 19:58:05 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	floodfill(t_data *data, int x, int y, char **map)
{
	if (x < 0 || y < 0 || x >= data->map_width || y >= data->map_height
		|| map[x][y] == 'X')
		return ;
	if (map[x][y] == '1')
		return ;
	if (map[x][y] == 'E')
	{
		map[x][y] = 'X';
		return ;
	}
	map[x][y] = 'X';
	floodfill(data, x + 1, y, map);
	floodfill(data, x - 1, y, map);
	floodfill(data, x, y + 1, map);
	floodfill(data, x, y - 1, map);
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

static int	check_closed(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	checkwalls(t_data *data)
{
	int	i;
	int	j;

	i = ft_strlen(data->map[0]);
	data->map_height = i;
	j = 0;
	while (data->map[j])
	{
		if (j == 0 || j == data->map_width - 1)
		{
			if (!check_closed(data->map[j]))
				return (ft_printf("Erreur\n"), 0);
		}
		else if (data->map[j][0] != '1' || data->map[j][i - 1] != '1')
			return (ft_printf("Erreur\n"), 0);
		j++;
	}
	return (1);
}

char	**getmap(t_data *data, int fd, char **map)
{
	while (fd)
	{
		data->line = get_next_line(fd);
		if (!data->line)
		{
			if (!data->buffer)
				return (ft_printf("Error\nempty file\n"), NULL);
			break ;
		}
		if (!data->buffer)
			data->buffer = ft_strdup2("");
		data->tmp = data->buffer;
		data->buffer = ft_strjoin2(data->tmp, data->line);
		if (error_map(data->line) == 1)
			data->erreur = 1;
		free_db(data->tmp, data->line);
		data->map_width++;
	}
	if (data->erreur == 1)
		return (free(data->buffer), NULL);
	map = ft_split(data->buffer, '\n');
	if (!map)
		return (free(data->buffer), NULL);
	return (free(data->buffer), map);
}

int	init_map(t_data *data, char *str)
{
	data->map = NULL;
	data->fd = 0;
	data->x = 0;
	data->y = 0;
	if (!check_extension(str))
	{
		ft_printf("Error\nWrong extension\n");
		return (0);
	}
	data->fd = open(str, O_RDONLY);
	if (data->fd == -1)
		return (ft_printf("Error\nFile not found\n"), 2);
	data->map = getmap(data, data->fd, data->map);
	if (!data->map)
		return (close(data->fd), 0);
	check_winnable(data);
	close(data->fd);
	return (1);
}