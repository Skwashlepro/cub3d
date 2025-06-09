/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:56:50 by luctan            #+#    #+#             */
/*   Updated: 2025/06/09 17:43:42 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_listener(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(data->display.map, data->display.mlx_win);
		ft_freedata(data);
		exit(0);
	}
	else if (keycode == W_KEY)
		fwd();
	else if (keycode == A_KEY)
		side(keycode);
	else if (keycode == D_KEY)
		side(keycode);
	else if (keycode == S_KEY)
		back();
}

int	on_window_close(t_data *data)
{
	ft_freedata(data);
	exit(0);
}
