/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 02:52:45 by luctan            #+#    #+#             */
/*   Updated: 2025/06/13 01:55:59 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ft_kill(t_data *data, int code)
{
	clear_db(data);
	mlx_destroy_window(data->display.mlx, data->display.mlx_win);
	mlx_destroy_display(data->display.mlx);
	free(data->display.mlx);
	exit(code);
}

int	on_window_close(t_data *data)
{
	ft_kill(data, 0);
	exit(0);
}