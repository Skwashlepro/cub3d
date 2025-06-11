/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:10:51 by luctan            #+#    #+#             */
/*   Updated: 2025/06/11 16:39:36 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->map = NULL;
	data->buffer = NULL;
	data->line = NULL;
	data->error = 0;
	data->map_height = 0;
	data->map_width = 0;
	data->fd = -1;
	data->p1.pos_x = 0;
	data->p1.pos_y = 0;
	data->p1.dir_x = 0;
	data->p1.dir_y = 0;
	data->p1.plane_x = 0;
	data->p1.plane_y = 0;
}

int	main(int ac, char **av, char *env[])
{
	t_data data;

	if (!env || !*env)
		return (1);
	else if (ac != 2)
		return (printf("INVALID ARGUMENT\n"), 0);
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data);
	if (!init_map(&data, av[1]))
		ft_kill(&data, 1);
	display_init(&data);
	ft_kill(&data, 0);
	return (0);
}
