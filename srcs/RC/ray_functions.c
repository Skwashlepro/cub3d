/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:10:51 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 18:13:18 by luctan           ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_walls(t_data *data, int x)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	tex_num;
	int	color;

	tex_num = get_wall_texture_num(data);
	y = data->ray.draw_start;
	while (y < data->ray.draw_end)
	{
		calculate_texture_coords(data, &tex_x, &tex_y, y);
		color = get_texture_color(data, tex_num, tex_x, tex_y);
		my_mlx_pixel_put(&data->frame, x, y, color);
		y++;
	}
}

void	dda(t_data *data)
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
