/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray-casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:29:51 by luctan            #+#    #+#             */
/*   Updated: 2025/06/13 17:29:58 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting(t_data *data)
{
	data->ray.hit = 0;
	data->ray.map_x = (int)data->p1.pos_x;
	data->ray.map_y = (int)data->p1.pos_y;
	data->ray.perp_wall_dist = 0;
	data->ray.camera_x = 0;
	data->ray.dir_x = 0;
	data->ray.dir_y = 0;
	data->ray.delta_dist_x = 0;
	data->ray.delta_dist_y = 0;
	data->ray.side_dist_x = 0;
	data->ray.side_dist_y = 0;
	data->ray.step_x = 0;
	data->ray.step_y = 0;
	data->ray.side = 0;
	data->ray.line_height = 0;
	data->ray.draw_start = 0;
	data->ray.draw_end = 0;
}

void	ray_steps(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->p1.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->p1.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->p1.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->p1.pos_y)
			* ray->delta_dist_y;
	}
}

void	init_ray(t_data *data, int x)
{
	t_ray	*ray;

	ray = &data->ray;
	init_raycasting(data);
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = data->p1.dir_x + data->p1.plane_x * ray->camera_x;
	ray->dir_y = data->p1.dir_y + data->p1.plane_y * ray->camera_x;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	cub_init(t_data *data)
{
	init_raycasting(data);
	raycast(data);
}

void	raycast(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, x);
		ray_steps(data);
		x++;
	}
}
