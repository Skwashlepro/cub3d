/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:03:15 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/06/08 02:10:15 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_map(t_data *data, char *str)
{
	char	*tmp;

	if (!check_extension(str))
	{
		printf("Error\nWrong extension\n");
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
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
            c == 'E' || c == 'W' || c == ' ');
}

void set_init_direction(t_data *data, char dir)
{
	data->p1.dir_x = 0;
	data->p1.dir_y = 0;
	data->p1.plane_x = 0;
	data->p1.plane_y = 0;

	if (dir == 'N')
	{
		data->p1.dir_y = -1; // la direction =/ au pointage de la camera.
		data->p1.plane_x = 0.66;// la camera pointe toujours a la droite du perso N = Droite du perso
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

static int	check_player(t_data *data)
{
    int	i;
    int	j;

    i = -1;
    while (data->map[++i])
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
                data->map[i][j] == 'E' || data->map[i][j] == 'W')
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

static char	**copy_map(char **map)
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
        reutrn(printf("Error\nInvalid player position or character\n"),0);
    if (!check_map_closed(data))
        return(printf("Error\nMap is not closed\n"),0);
    return (1);
}