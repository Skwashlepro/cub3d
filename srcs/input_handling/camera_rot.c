/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:52:49 by luctan            #+#    #+#             */
/*   Updated: 2025/06/23 17:07:56 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_cam(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->p1.dir_x;
	data->p1.dir_x = data->p1.dir_x * cos(rot_speed) - data->p1.dir_y * sin(rot_speed);
	data->p1.dir_y = old_dir_x * sin(rot_speed) + data->p1.dir_y * cos(rot_speed);
	old_plane_x = data->p1.plane_x;
	data->p1.plane_x = data->p1.plane_x * cos(rot_speed) - data->p1.plane_y * sin(rot_speed);
	data->p1.plane_y = old_plane_x * sin(rot_speed) + data->p1.plane_y * cos(rot_speed);
}

int	mouse_mov(int x, int y, t_data *data)
{
    static int	ignore_next = 0;
    double		delta_x;

    (void)y;
    if (ignore_next)
    {
        ignore_next = 0;
        return (0);
    }
    delta_x = x - (WIDTH / 2);
    if (delta_x != 0)
        rot_cam(data, delta_x * 0.003); // Adjust sensitivity as needed
    mlx_mouse_move(data->display.mlx, data->display.mlx_win, WIDTH / 2, HEIGHT / 2);
    ignore_next = 1;
    return (0);
}

