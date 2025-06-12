/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:03:15 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/06/13 01:58:06 by luctan           ###   ########.fr       */
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
	if (checkcardinal(&data->gfx, data->fd) != 6)
		return (printf("Error\n Invalid textures path \n"), 0);
	data->map = getmap(data, data->fd, data->map, tmp);
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

void	set_init_direction(t_data *data, char dir)
{
	data->p1.dir_x = 0;
	data->p1.dir_y = 0;
	data->p1.plane_x = 0;
	data->p1.plane_y = 0;
	if (dir == 'N')
	{
		data->p1.dir_y = -1; // la direction =/ au pointage de la camera.
		data->p1.plane_x = 0.66;
		// la camera pointe toujours a la droite du perso N = Droite du perso
	}
	else if (dir == 'S')
	{
		data->p1.dir_y = 1;
		data->p1.plane_x = -0.66;
	}
	else if (dir == 'W')
	{
		data->p1.dir_x = -1;
		data->p1.plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		data->p1.dir_x = 1;
		data->p1.plane_y = 0.66;
	}
}

int	check_player(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->p1.pos_x = j + 0.5;
				data->p1.pos_y = i + 0.5;
				set_init_direction(data, data->map[i][j]);
				data->map[i][j] = '0';
				return (1);
			}
			else if (!is_valid_char(data->map[i][j]))
				return (0);
		}
	}
	return (0);
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

static int	check_texture(char **split, char **wall_texture, int *count)
{
	if (ft_strchr(split[1], '.') && ft_strcmp(ft_strrchr(split[1], '.'),
			".xpm\n") == 0)
	{
		*wall_texture = ft_strdup(split[1]);
		free(wall_texture[0]);
		(*count)++;
		return (1);
	}
	return (0);
}

static int	check_color(char **split, unsigned int *color, int *count)
{
	int	r;
	int	g;
	int	b;
	char **tmp;

	tmp = ft_split(split[1], ',');
	if (!tmp)
		return (0);
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
	}
	free_array(tmp);
	return (0);
}

static int	process_cardinal(char **split, t_gfx *gfx, int *found_count)
{
	if (!split[0] || !split[1])
		return (0);
	if (!ft_strncmp(split[0], "NO", 3) && check_texture(split,
			&gfx->wall_path[0], found_count))
		return (1);
	if (!ft_strncmp(split[0], "SO", 3) && check_texture(split,
			&gfx->wall_path[1], found_count))
		return (1);
	if (!ft_strncmp(split[0], "WE", 3) && check_texture(split,
			&gfx->wall_path[2], found_count))
		return (1);
	if (!ft_strncmp(split[0], "EA", 3) && check_texture(split,
			&gfx->wall_path[3], found_count))
		return (1);
	if (!ft_strncmp(split[0], "C", 2) && check_color(split, &gfx->ceiling_color,
			found_count))
		return (1);
	if (!ft_strncmp(split[0], "F", 2) && check_color(split, &gfx->floor_color,
			found_count))
		return (1);
	return (0);
}

int	checkcardinal(t_gfx *gfx, int fd)
{
	char	*line;
	char	**split;
	int		found_count;
	
	found_count = 0;
	while (found_count < 6)
	{
		line = get_next_line(fd);
		if(!line)
			break ;
		split = ft_split(line, ' ');
		free_str(line);
		if (!split)
			continue ;
		process_cardinal(split, gfx, &found_count);
		free_array(split);
	}
	return (found_count);
}

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