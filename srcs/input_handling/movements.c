/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 02:21:46 by luctan            #+#    #+#             */
/*   Updated: 2025/06/26 15:09:09 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fwd(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->p1.pos_x + data->p1.dir_x * 0.1;
	new_y = data->p1.pos_y + data->p1.dir_y * 0.1;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->p1.pos_x = new_x;
		data->p1.pos_y = new_y;
	}
}

void	back(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->p1.pos_x - data->p1.dir_x * 0.1;
	new_y = data->p1.pos_y - data->p1.dir_y * 0.1;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->p1.pos_x = new_x;
		data->p1.pos_y = new_y;
	}
}

void	side(t_data *data, int keycode)
{
	double	new_x;
	double	new_y;

	new_x = data->p1.pos_x;
	new_y = data->p1.pos_y;
	if (keycode == A_KEY)
	{
		new_x = data->p1.pos_x - data->p1.plane_x * 0.1;
		new_y = data->p1.pos_y - data->p1.plane_y * 0.1;
	}
	else if (keycode == D_KEY)
	{
		new_x = data->p1.pos_x + data->p1.plane_x * 0.1;
		new_y = data->p1.pos_y + data->p1.plane_y * 0.1;
	}
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->p1.pos_x = new_x;
		data->p1.pos_y = new_y;
	}
}

void	movements(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		fwd(data);
	else if (keycode == S_KEY)
		back(data);
	else if (keycode == A_KEY || keycode == D_KEY)
		side(data, keycode);
}
