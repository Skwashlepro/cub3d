/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:52:49 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 18:40:54 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_cam(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->p1.dir_x;
	data->p1.dir_x = data->p1.dir_x * cos(rot_speed) - data->p1.dir_y
		* sin(rot_speed);
	data->p1.dir_y = old_dir_x * sin(rot_speed) + data->p1.dir_y
		* cos(rot_speed);
	old_plane_x = data->p1.plane_x;
	data->p1.plane_x = data->p1.plane_x * cos(rot_speed) - data->p1.plane_y
		* sin(rot_speed);
	data->p1.plane_y = old_plane_x * sin(rot_speed) + data->p1.plane_y
		* cos(rot_speed);
}

int	mouse_mov(int x, int y, t_data *data)
{
	static int	ignore_next = 0;
	int			center_x;
	double		delta_x;

	center_x = WIDTH / 2;
	(void)y;
	if (ignore_next)
	{
		ignore_next = 0;
		return (0);
	}
	if (x != center_x)
	{
		delta_x = x - center_x;
		rot_cam(data, delta_x * M_SENS); // Adjust sensitivity
		mlx_mouse_move(data->display.mlx, data->display.mlx_win, center_x,
			HEIGHT / 2);
		ignore_next = 1;
	}
	data->redraw = 1; // Trigger redraw after mouse movement
	return (0);
}
