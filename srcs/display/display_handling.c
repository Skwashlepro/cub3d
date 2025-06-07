/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:55:38 by luctan            #+#    #+#             */
/*   Updated: 2025/06/07 02:33:27 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_data *data)
{
	Ay         = floor(player_y / TILE) * TILE;
	if (RayFacingDown)
	Ay += TILE;

	// tan(α)  = Opposite / Adjacent;
	// tan(α)  = (Ay - Py) / (Ax - Px);
	// Ax - Px = (Ay - Py) / tan(α);
	Ax         = Px + (Ay - Py) / tan(α);

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
