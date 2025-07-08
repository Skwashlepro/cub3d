/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:45 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 18:12:55 by luctan           ###   ########.fr       */
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
