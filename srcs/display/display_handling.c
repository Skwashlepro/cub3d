/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:55:38 by luctan            #+#    #+#             */
/*   Updated: 2025/06/10 19:49:22 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_data *data)
{
	text_init(data);
}

int	render_frame(t_data *data)
{
	t_img	frame;
	int		x;
	int		y;
	
	y = -1;
	frame.img = mlx_new_image(data->display.mlx, WIDTH, HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_length, &frame.endian);
	if (!frame.img || !frame.addr)
		return (printf("Error: Failed to create image\n"), 0);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_pixel_put(data->display.mlx, data->display.mlx_win, x, y, data->gfx.ceiling_color);
			else
				mlx_pixel_put(data->display.mlx, data->display.mlx_win, x, y, data->gfx.floor_color);
		}
	}
	mlx_put_image_to_window(data->display.mlx, data->display.mlx_win, frame.img, 0, 0);
	mlx_destroy_image(data->display.mlx, frame.img);
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
	// mlx_hook(disp->mlx_win, 2, 1L << 0, &key_listener, data);
	mlx_loop_hook(disp->mlx, render_frame, data);
	mlx_hook(disp->mlx_win, 17, 0, on_window_close, data);
	mlx_loop(disp->mlx);
	if (disp->mlx == 0)
		return ;
}
