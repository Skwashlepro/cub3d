/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:45 by luctan            #+#    #+#             */
/*   Updated: 2025/07/14 17:47:45 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_init_direction(t_data *data, char dir)
{
	data->p1.dir_x = 0;
	data->p1.dir_y = 0;
	data->p1.plane_x = 0;
	data->p1.plane_y = 0;
	if (dir == 'N')
	{
		data->p1.dir_y = -1;
		data->p1.plane_x = 0.9;
	}
	else if (dir == 'S')
	{
		data->p1.dir_y = 1;
		data->p1.plane_x = -0.9;
	}
	else if (dir == 'W')
	{
		data->p1.dir_x = -1;
		data->p1.plane_y = -0.9;
	}
	else if (dir == 'E')
	{
		data->p1.dir_x = 1;
		data->p1.plane_y = 0.9;
	}
}

int	checkcardinal(t_gfx *gfx, int fd)
{
	char	*line;
	char	**split;
	int		found_count;

	found_count = 0;
	while (found_count < 6)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		split = ft_split(line, ' ');
		free_str(line);
		if (!split)
			continue ;
		if (!process_cardinal(split, gfx, &found_count))
		{
			found_count = -1;
			get_next_line(fd, 1);
			free_array(split);
			break ;
		}
		free_array(split);
	}
	return (found_count);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

void	is_player(t_data *data, int i, int j, int *found_player)
{
	if (*found_player)
		return ;
	data->p1.pos_x = j + 0.5;
	data->p1.pos_y = i + 0.5;
	set_init_direction(data, data->map[i][j]);
	data->map[i][j] = '0';
	*found_player = 1;
}

int	space_in_map(char *map)
{
	int	i;

	i = -1;
	while (map[++i])
		if (map[i] == '1')
			break ;
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			while (map[++i] && map[i] == '\n')
				;
			if (map[i])
				return (0);
		}
		else
			i++;
	}
	return (1);
}
