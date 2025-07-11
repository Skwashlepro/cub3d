/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:29:16 by lmokhtar          #+#    #+#             */
/*   Updated: 2025/07/11 19:30:07 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_normalized_row(char *new_row, char *old_row, int max_width)
{
	int	j;

	j = -1;
	while (++j < max_width)
	{
		if (j < (int)ft_strlen(old_row))
		{
			if (old_row[j] == ' ')
				new_row[j] = '1';
			else
				new_row[j] = old_row[j];
		}
		else
			new_row[j] = '1';
	}
	new_row[max_width] = '\0';
}

void	normalize_map(t_data *data)
{
	int		i;
	int		max_width;
	char	*new_row;

	max_width = 0;
	i = -1;
	while (++i < data->map_height)
		if ((int)ft_strlen(data->map[i]) > max_width)
			max_width = ft_strlen(data->map[i]);
	i = -1;
	while (++i < data->map_height)
	{
		new_row = malloc(sizeof(char) * (max_width + 1));
		if (!new_row)
			return ;
		fill_normalized_row(new_row, data->map[i], max_width);
		free(data->map[i]);
		data->map[i] = new_row;
	}
	data->map_width = max_width;
}
