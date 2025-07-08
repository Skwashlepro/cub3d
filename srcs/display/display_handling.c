/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:55:38 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 17:52:13 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_data *data)
{
	text_init(data);
}

void	render_frame(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;
	char			*dst;

	y = -1;
	if (!data->frame.img || !data->frame.addr)
		return ((void)printf("Error: Failed to create image\n"));
	while (++y < HEIGHT)
	{
		x = -1;
		if (y < HEIGHT / 2)
			color = data->gfx.ceiling_color;
		else
			color = data->gfx.floor_color;
		while (++x < WIDTH)
		{
			dst = data->frame.addr + (y * data->frame.line_length + x
					* (data->frame.bpp / 8));
			*(unsigned int *)dst = color;
		}
	}
	cub_init(data);
	mlx_put_image_to_window(data->display.mlx, data->display.mlx_win,
		data->frame.img, 0, 0);
}

int	cub_loop(t_data *data)
{
	if (data->keys.turn_left || data->keys.turn_right)
	{
		if (data->keys.turn_left)
			rot_cam(data, -ROT_SPEED);
		if (data->keys.turn_right)
			rot_cam(data, ROT_SPEED);
		data->redraw = 1;
	}
	if (data->keys.up)
		movements(W_KEY, data);
	if (data->keys.down)
		movements(S_KEY, data);
	if (data->keys.left)
		movements(A_KEY, data);
	if (data->keys.right)
		movements(D_KEY, data);
	if (data->redraw)
	{
		data->redraw = 0;
		render_frame(data);
	}
	return (0);
}

void	display_init(t_data *data)
{
	t_disp	*disp;
	t_img	*frame;

	frame = &data->frame;
	disp = &(data->display);
	disp->mlx = mlx_init();
	disp->mlx_win = mlx_new_window(disp->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data || !data->display.mlx || !data->display.mlx_win)
		return ;
	mlx_mouse_hide(disp->mlx, disp->mlx_win);
	mlx_hook(disp->mlx_win, 2, 1L << 0, key_listener, data);
	mlx_hook(disp->mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(disp->mlx_win, 6, 1L << 6, mouse_mov, data);
	cub3d(data);
	frame->img = mlx_new_image(data->display.mlx, WIDTH, HEIGHT);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp,
			&frame->line_length, &frame->endian);
	mlx_loop_hook(disp->mlx, cub_loop, data);
	mlx_hook(disp->mlx_win, 17, 0, on_window_close, data);
	mlx_loop(disp->mlx);
	if (disp->mlx == 0)
		return ;
}
