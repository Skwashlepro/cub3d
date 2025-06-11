/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 02:52:45 by luctan            #+#    #+#             */
/*   Updated: 2025/06/11 18:48:32 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_kill(t_data *data, int code)
{
	free_array(data->map);
	mlx_destroy_image(data->display.mlx, data->frame.img);
	mlx_destroy_display(data->display.mlx);
	free(data->display.mlx);
	free(data);
	exit(code);
}

int	on_window_close(t_data *data)
{
	ft_kill(data, 0);
	exit(0);
}