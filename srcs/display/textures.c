/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:38:10 by luctan            #+#    #+#             */
/*   Updated: 2025/06/14 01:22:29 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(int i, t_data *data)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (data->gfx.wall[j])
			mlx_destroy_image(data->display.mlx, data->gfx.wall[j]);
		j++;
	}
	if (data->gfx.viewmodel)
		mlx_destroy_image(data->display.mlx, data->gfx.viewmodel);
	ft_kill(data, 1);
}

int	text_load(t_data *data, char *PATH, void **texture)
{
	t_disp	*disp;
	int		width;
	int		height;

	width = 0;
	height = 0;
	disp = &data->display;
	if (!disp->mlx)
		return (printf("Error:\n \tDisplay not initialized.\n"), 0);
	*texture = mlx_xpm_file_to_image(disp->mlx, PATH, &width,
			&height);
	if (!*texture)
		return (printf("Error:\n \tFailed to load texture: %s\n", PATH), 0);
	return (1);
}

void	text_init(t_data *data)
{
	t_gfx *text;
	int i;

	i = -1;
	text = &data->gfx;
	while (++i < 4)
		if (!text_load(data, text->wall_path[i], &text->wall[i]))
			free_textures(i, data); // a changer pour clear les textures si > N
}

int	get_texture_color(t_data *data, int tex_num, int tex_x, int tex_y)
{
    t_img	tex_img;
    char	*pixel;
    int		color;
    int		tex_width = 64;
    int		tex_height = 64;

    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex_width) tex_x = tex_width - 1;
    if (tex_y < 0) tex_y = 0;
    if (tex_y >= tex_height) tex_y = tex_height - 1;

    tex_img.addr = mlx_get_data_addr(data->gfx.wall[tex_num],
        &tex_img.bpp, &tex_img.line_length, &tex_img.endian);
    if (!tex_img.addr)
        return (0x808080);
    pixel = tex_img.addr + (tex_y * tex_img.line_length + tex_x * (tex_img.bpp / 8));
    color = *(int*)pixel;
    return (color);
}

void	calculate_texture_coords(t_data *data, int *tex_x, int *tex_y, int screen_y)
{
    double	wall_x;
    double	step;
    double	tex_pos;
    int		tex_height = 64;

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
            return (3); // EA
        else
            return (2); // WE
    }
    else // EW walls
    {
        if (data->ray.dir_y > 0)
            return (1); // SO
        else
            return (0); // NO
    }
}
