/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 02:52:45 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 20:03:55 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_kill(t_data *data, int code)
{
	if (data)
		clear_db(data);
	if (data->display.mlx_win && data->display.mlx)
	{
		mlx_destroy_window(data->display.mlx, data->display.mlx_win);
		mlx_destroy_display(data->display.mlx);
		free(data->display.mlx);
	}
	exit(code);
}

int	on_window_close(t_data *data)
{
	ft_kill(data, 0);
	exit(0);
}
