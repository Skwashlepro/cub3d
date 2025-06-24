/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:56:50 by luctan            #+#    #+#             */
/*   Updated: 2025/06/23 15:37:46 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_listener(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		ft_kill(data, 0);
	// else if (ft_strchr("WASD", keycode))
	// 	movements(keycode, data);
	else if (keycode == LEFT_KEY)
		rot_cam(data, -ROT_SPEED);
	else if (keycode == RIGHT_KEY)
		rot_cam(data, ROT_SPEED);
	return (0);
}



