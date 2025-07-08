/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:38:10 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 17:53:06 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	text_load(t_data *data, char *PATH, t_img *img)
{
	t_disp	*disp;
	int		width;
	int		height;

	width = 0;
	height = 0;
	disp = &data->display;
	if (!disp->mlx)
		return (printf("Error:\n \tDisplay not initialized.\n"), 0);
	img->img = mlx_xpm_file_to_image(disp->mlx, PATH, &width, &height);
	img->width = width;
	img->height = height;
	if (width <= 0 || height <= 0)
		return (printf("Error:\n \tInvalid texture dimensions: %s\n", PATH), 0);
	if (!img->img)
		return (printf("Error:\n \tFailed to load texture: %s\n", PATH), 0);
	return (1);
}

void	text_init(t_data *data)
{
	t_gfx	*text;
	int		i;

	i = -1;
	text = &data->gfx;
	while (++i < 4)
	{
		if (!text_load(data, text->wall_path[i], &text->wall[i]))
			free_textures(i, data);
		text->wall[i].addr = mlx_get_data_addr(text->wall[i].img,
				&text->wall[i].bpp, &text->wall[i].line_length,
				&text->wall[i].endian);
	}
}

int	get_texture_color(t_data *data, int tex_num, int tex_x, int tex_y)
{
	t_img	tex_img;
	char	*pixel;
	int		color;

	(void)data;
	tex_img = data->gfx.wall[tex_num];
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_img.width)
		tex_x = tex_img.width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_img.height)
		tex_y = tex_img.height - 1;
	pixel = tex_img.addr + (tex_y * tex_img.line_length + tex_x * (tex_img.bpp
				/ 8));
	color = *(int *)pixel;
	return (color);
}

void	calculate_texture_coords(t_data *data, int *tex_x, int *tex_y,
		int screen_y)
{
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_height;

	tex_height = 64;
	if (data->ray.side == 0)
		wall_x = data->p1.pos_y + data->ray.perp_wall_dist * data->ray.dir_y;
	else
		wall_x = data->p1.pos_x + data->ray.perp_wall_dist * data->ray.dir_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * tex_height);
	if (data->ray.side == 0 && data->ray.dir_x > 0)
		*tex_x = tex_height - *tex_x - 1;
	if (data->ray.side == 1 && data->ray.dir_y < 0)
		*tex_x = tex_height - *tex_x - 1;
	step = 1.0 * tex_height / data->ray.line_height;
	tex_pos = (screen_y - HEIGHT / 2 + data->ray.line_height / 2) * step;
	*tex_y = (int)tex_pos & (tex_height - 1);
}

int	get_wall_texture_num(t_data *data)
{
	if (data->ray.side == 0)
	{
		if (data->ray.dir_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (data->ray.dir_y > 0)
			return (1);
		else
			return (0);
	}
}
