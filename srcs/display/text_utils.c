/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:53:24 by luctan            #+#    #+#             */
/*   Updated: 2025/07/08 17:53:36 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(int i, t_data *data)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (data->gfx.wall[j].img)
			mlx_destroy_image(data->display.mlx, data->gfx.wall[j].img);
		j++;
	}
	if (data->gfx.viewmodel)
		mlx_destroy_image(data->display.mlx, data->gfx.viewmodel);
	ft_kill(data, 1);
}
