/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:55:38 by luctan            #+#    #+#             */
/*   Updated: 2025/06/08 00:40:43 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_data *data)
{
	
}

void	display_init(t_data *data)
{
	t_disp	*disp;

	disp = &(data->display);
	disp->mlx = mlx_init();
	disp->mlx_win = mlx_new_window(disp->mlx, WIDTH, HEIGHT, "Cub3D");
	cub3d(&data);
	// mlx_hook(disp->mlx_win, 2, 1L << 0, &key_listener, data);
	mlx_hook(disp->mlx_win, 17, 0, on_window_close, data);
	mlx_loop(disp->mlx);
	if (disp->mlx == 0)
		return ;
}
