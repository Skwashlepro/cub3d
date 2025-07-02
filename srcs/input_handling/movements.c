/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 02:21:46 by luctan            #+#    #+#             */
/*   Updated: 2025/07/02 02:54:00 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fwd(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->p1.pos_x + data->p1.dir_x * MOVE_SPEED;
	new_y = data->p1.pos_y + data->p1.dir_y * MOVE_SPEED;
	if (data->map[(int)data->p1.pos_y][(int)new_x] != '1')
		data->p1.pos_x = new_x;
	if (data->map[(int)new_y][(int)data->p1.pos_x] != '1')
		data->p1.pos_y = new_y;
}

void	back(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->p1.pos_x - data->p1.dir_x * MOVE_SPEED;
	new_y = data->p1.pos_y - data->p1.dir_y * MOVE_SPEED;
	if (data->map[(int)data->p1.pos_y][(int)new_x] != '1')
		data->p1.pos_x = new_x;
	if (data->map[(int)new_y][(int)data->p1.pos_x] != '1')
		data->p1.pos_y = new_y;
}

void	side(t_data *data, int keycode)
{
    if (keycode == A_KEY)
    {
        double new_x = data->p1.pos_x - data->p1.plane_x * MOVE_SPEED;
        double new_y = data->p1.pos_y - data->p1.plane_y * MOVE_SPEED;
        if (data->map[(int)data->p1.pos_y][(int)new_x] != '1')
            data->p1.pos_x = new_x;
        if (data->map[(int)new_y][(int)data->p1.pos_x] != '1')
            data->p1.pos_y = new_y;
    }
    else if (keycode == D_KEY)
    {
        double new_x = data->p1.pos_x + data->p1.plane_x * MOVE_SPEED;
        double new_y = data->p1.pos_y + data->p1.plane_y * MOVE_SPEED;
        if (data->map[(int)data->p1.pos_y][(int)new_x] != '1')
            data->p1.pos_x = new_x;
        if (data->map[(int)new_y][(int)data->p1.pos_x] != '1')
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
	data->redraw = 1;
}
