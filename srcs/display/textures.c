/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:38:10 by luctan            #+#    #+#             */
/*   Updated: 2025/06/13 01:33:11 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(int i, t_data *data)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (data->gfx.wall[j])
			mlx_destroy_image(data->display.mlx, data->gfx.wall[j]);
		j++;
	}
	if (data->gfx.viewmodel)
		mlx_destroy_image(data->display.mlx, data->gfx.viewmodel);
	ft_kill(data, 1);
}

int	text_load(t_data *data, char *PATH, void **texture)
{
	t_disp	*disp;
	int		width;
	int		height;

	width = 0;
	height = 0;
	disp = &data->display;
	(void)PATH;
	*texture = mlx_xpm_file_to_image(disp->mlx, "textures/mur.xpm",
			&width, &height);
	if (!*texture)
		return (printf("Error: Failed to load texture: %s\n", PATH), 0);
	return (1);
}

void	text_init(t_data *data)
{
	t_gfx	*text;
	int		i;

	i = -1;
	text = &data->gfx;
	while (++i < 4)
		if (!text_load(data, text->wall_path[i], &text->wall[i]))
			free_textures(i, data); // a changer pour clear les textures si > N
}