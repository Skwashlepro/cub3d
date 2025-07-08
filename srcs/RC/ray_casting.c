/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:29:51 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 18:13:16 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	wall_distance(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->p1.pos_x + (1 - ray->step_x)
				/ 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->p1.pos_y + (1 - ray->step_y)
				/ 2) / ray->dir_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	raycast(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, x);
		ray_steps(data);
		dda(data);
		wall_distance(data);
		draw_walls(data, x);
		x++;
	}
}

void	cub_init(t_data *data)
{
	init_raycasting(data);
	raycast(data);
}
