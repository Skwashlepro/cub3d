/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:44:35 by luctan            #+#    #+#             */
/*   Updated: 2025/06/26 17:28:14 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return ;
}

void	free_db(char *str, char *str2)
{
	free_str(str);
	free_str(str2);
	return ;
}

int	check_extension(char *fichier)
{
	char	*ext;

	ext = ft_strchr(fichier, '.');
	if (ext != NULL && ft_strcmp(ext, ".cub") == 0)
		return (1);
	printf("Error\nWrong ext\n");
	return (0);
}

void free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void clear_db(t_data *data)
{
	t_gfx	*gfx;
	int	i;

	i = -1;
	gfx = &data->gfx;
	if (data->frame.img)
		mlx_destroy_image(data->display.mlx, data->frame.img); ;
	while (gfx->wall[++i].img)
	{
		mlx_destroy_image(data->display.mlx, gfx->wall[i].img);
		gfx->wall[i].img = NULL;
	}
	i = -1;
	while (gfx->wall_path[++i])
		free_str(gfx->wall_path[i]);
	if (data->line)
		free_str(data->line);
	if (data->map)
		free_array(data->map);
}
