/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray-casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:29:51 by luctan            #+#    #+#             */
/*   Updated: 2025/06/19 03:29:27 by luctan           ###   ########.fr       */
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
		ray->step_x = -1; // a gauche
		ray->side_dist_x = (data->p1.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1; // a droite
		ray->side_dist_x = (ray->map_x + 1.0 - data->p1.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1; // en haut
		ray->side_dist_y = (data->p1.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1; // en bas
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

void	DDA(t_data *data)
{
	t_ray	*ray;

	ray = &data->ray;
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char	*dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

void	draw_walls(t_data *data, int x)
{
	t_ray	*ray;
	t_img	*frame;
	int		y;
	int		color;

	ray = &data->ray;
	frame = &data->frame;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		if (ray->side == 0)
			color = (ray->step_x > 0) ? 0xFF0000 : 0x00FF00; // Red for vertical walls, Green for horizontal
		else
			color = (ray->step_y > 0) ? 0x0000FF : 0xFFFF00; // Blue for horizontal walls, Yellow for vertical
		my_mlx_pixel_put(frame, x, y, color);
		y++;
	}
}

void	raycast(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, x);
		ray_steps(data);
		DDA(data);
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
