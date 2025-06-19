/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:55:38 by luctan            #+#    #+#             */
/*   Updated: 2025/06/19 03:16:42 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_data *data)
{
	text_init(data);
}

int	render_frame(t_data *data)
{
	t_img			*frame;
	int				x;
	int				y;
	unsigned int	color;
	char			*dst;

	y = -1;
	frame = &data->frame;
	frame->img = mlx_new_image(data->display.mlx, WIDTH, HEIGHT);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp,
			&frame->line_length, &frame->endian);
	if (!frame->img || !frame->addr)
		return (printf("Error: Failed to create image\n"), 0);
	while (++y < HEIGHT)
	{
		x = -1;
		color = (y < HEIGHT
				/ 2) ? data->gfx.ceiling_color : data->gfx.floor_color;
		while (++x < WIDTH)
		{
			dst = frame->addr + (y * frame->line_length + x * (frame->bpp / 8));
			*(unsigned int *)dst = color;
		}
	}
	cub_init(data);
	mlx_put_image_to_window(data->display.mlx, data->display.mlx_win,
		frame->img, 0, 0);
	mlx_destroy_image(data->display.mlx, frame->img);
	return (0);
}

void	display_init(t_data *data)
{
	t_disp	*disp;

	disp = &(data->display);
	disp->mlx = mlx_init();
	disp->mlx_win = mlx_new_window(disp->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data || !data->display.mlx || !data->display.mlx_win)
		return ;
	cub3d(data);
	mlx_hook(disp->mlx_win, 2, 1L << 0, &key_listener, data);
	mlx_loop_hook(disp->mlx, render_frame, data);
	mlx_hook(disp->mlx_win, 17, 0, on_window_close, data);
	mlx_loop(disp->mlx);
	if (disp->mlx == 0)
		return ;
}
