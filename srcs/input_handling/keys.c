/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:56:50 by luctan            #+#    #+#             */
/*   Updated: 2025/06/11 18:48:45 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_listener(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		ft_kill(data, 0);
	// else if (keycode == W_KEY)
	// 	fwd();
	// else if (keycode == A_KEY)
	// 	side(keycode);
	// else if (keycode == D_KEY)
	// 	side(keycode);
	// else if (keycode == S_KEY)
	// 	back;
	return (0);
}

