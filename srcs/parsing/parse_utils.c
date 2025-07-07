/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:31:57 by luctan            #+#    #+#             */
/*   Updated: 2025/07/07 20:56:07 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**check_rgb(char *split)
{
	char	**tmp;
	char	*trim;
	int		i;
	int		j;

	i = -1;
	tmp = ft_split(split, ',');
	trim = ft_strtrim(tmp[2], "\n");
	free_str(tmp[2]);
	tmp[2] = ft_strdup(trim);
	free_str(trim);
	while (tmp[++i])
	{
		j = -1;
		while (tmp[i][++j])
			if ((tmp[i][j] < '0' || tmp[i][j] > '9'))
				return (free_array(tmp), NULL);
	}
	return (tmp);
}
