/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:03:15 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/07/08 18:25:11 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_map(t_data *data, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (!check_extension(str))
		return (printf("Error\n Wrong extension\n"), 0);
	data->fd = open(str, O_RDONLY);
	if (data->fd == -1)
		return (printf("Error\nFile not found\n"), 2);
	if (checkcardinal(&data->gfx, data->fd) != 6)
		return (printf("Error\n Invalid textures path \n"), 0);
	data->map = getmap(data, data->fd, data->map, tmp);
	if (!data->map)
		return (close(data->fd), 0);
	if (!valid_map(data))
	{
		free_array(data->map);
		data->map = NULL;
		return (printf("Error\n Invalid map\n"), 0);
	}
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
	int	found_player;

	i = -1;
	found_player = 0;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				if (found_player)
					return (0);
				data->p1.pos_x = j + 0.5;
				data->p1.pos_y = i + 0.5;
				set_init_direction(data, data->map[i][j]);
				data->map[i][j] = '0';
				found_player = 1;
			}
			else if (!is_valid_char(data->map[i][j]))
				return (0);
		}
	}
	return (found_player);
}

int	check_texture(char **split, char **wall_texture, int *count)
{
	if (ft_strchr(split[1], '.') && ft_strcmp(ft_strrchr(split[1], '.'),
			".xpm\n") == 0)
	{
		*wall_texture = ft_strtrim(split[1], "\n");
		if (access(*wall_texture, F_OK) == -1)
		{
			printf("Error\n Texture file %s not found\n", split[1]);
			return (0);
		}
		(*count)++;
		return (1);
	}
	return (0);
}

int	check_color(char **split, unsigned int *color, int *count)
{
	int		r;
	int		g;
	int		b;
	char	**tmp;

	tmp = check_rgb(split[1]);
	if (tmp)
	{
		r = ft_atoi(tmp[0]);
		g = ft_atoi(tmp[1]);
		b = ft_atoi(tmp[2]);
		if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		{
			*color = (r << 16) | (g << 8) | b;
			(*count)++;
			return (free_array(tmp), 1);
		}
		free_array(tmp);
	}
	else
		return (1);
	return (0);
}
