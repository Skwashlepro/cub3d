/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:38:10 by luctan            #+#    #+#             */
/*   Updated: 2025/06/09 04:07:34 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	text_load(t_data *data, char *PATH, void **texture)
{
	t_disp	*disp;
	int		width = 0;
	int		height = 0;

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

	text = &data->gfx;
	if (!text_load(data, "./textures/north.xpm", &text->wall[N]))
		ft_kill(data, 1); // a changer pour clear les textures si > N
	if (!text_load(data, "./textures/south.xpm", &text->wall[S]))
		ft_kill(data, 1);
	if (!text_load(data, "./textures/west.xpm", &text->wall[W]))
		ft_kill(data, 1);
	if (!text_load(data, "./textures/east.xpm", &text->wall[E]))
		ft_kill(data, 1);
}