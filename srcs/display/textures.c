/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:38:10 by luctan            #+#    #+#             */
/*   Updated: 2025/06/09 19:33:03 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(int i, t_gfx *text, t_disp *disp, t_data *data)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (text->wall[j])
			mlx_destroy_image(disp->mlx, text->wall[j]);
		j++;
	}
	if (text->viewmodel)
		mlx_destroy_image(disp->mlx, text->viewmodel);
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
	*texture = mlx_xpm_file_to_image(disp->mlx, PATH,
			&width, &height);
	if (!*texture)
		return (ft_printf("Error: Failed to load texture: %s\n", PATH), 0);
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
			free_textures(i, text, &data->display, data); // a changer pour clear les textures si > N
}