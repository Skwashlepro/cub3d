/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 02:21:46 by luctan            #+#    #+#             */
/*   Updated: 2025/06/23 15:27:34 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fwd(t_data *data);

void	back(t_data *data);

void	movements(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		fwd(data);
	else if (keycode == S_KEY)
		back(data);
	else if (keycode == A_KEY || keycode == D_KEY)
		side(data, keycode);
}
