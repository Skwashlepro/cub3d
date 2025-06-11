/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:48:20 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/06/11 16:12:36 by lmokhtar         ###   ########.fr       */
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
	int				i;
	int				j;
	char			**map_copy;

	map_copy = copy_map(data->map);
	if (!map_copy)
		return (0);
	floodfill(data, data->p1.pos_x, data->p1.pos_y, map_copy);
	i = 0;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == '0')
			{
				return (free_map(map_copy), 0);
			}
			j++;
		}
		i++;
	}
	free_map(map_copy);
	return (1);
}

int	checkwalls(t_data *data)
{
	int	i;
	int	j;

	i = ft_strlen(data->map[0]);
	data->map_width = i;
	j = 0;
	while (data->map[j])
	{
		if (j == 0 || j == data->map_width - 1)
		{
			if (!check_closed(data))
				return (printf("Erreur\n"), 0);
		}
		else if (data->map[j][0] != '1' || data->map[j][i - 1] != '1')
			return (printf("Erreur\n"), 0);
		j++;
	}
	return (1);
}

char	**getmap(t_data *data, int fd, char **map, char *tmp)
{
	while (fd)
	{
		data->line = get_next_line(fd);
		// printf("line: %s\n", data->line);
		if (!data->line)
		{
			if (!data->buffer)
				return (printf("Error\nempty file\n"), NULL);
			break ;
		}
		if (!data->buffer) // ca sert a quoi ? / je sais meme plus mdrrr jle met en commentaire pour l'instant
				data->buffer = ft_strdup2("");
			tmp = data->buffer;
		data->buffer = ft_strjoin2(tmp, data->line);
		if (error_map(data->line) == 1) // change enleve le "if" et change data->error dans error_map ca fait gagner des lignes et c'est +1000 aura data->error = 1;
			free_db(tmp, data->line);	
		data->map_width++;
	}
	if (data->error == 1)
		return (free_str(data->buffer), NULL);
	map = ft_split(data->buffer, '\n');
	if (!map)
		return (free_str(data->buffer), NULL);
	return (free_str(data->buffer), map);
}
