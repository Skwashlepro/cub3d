/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:56:50 by luctan            #+#    #+#             */
/*   Updated: 2025/07/02 02:31:32 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_listener(int keycode, t_data *data)
{
	t_keys	*keys;

	keys = &data->keys;
	if (keycode == ESC_KEY)
		ft_kill(data, 0);
	else if (keycode == LEFT_KEY)
		keys->turn_left = 1;
	else if (keycode == RIGHT_KEY)
		keys->turn_right = 1;
	else if (keycode == W_KEY)
		keys->up = 1;
	else if (keycode == S_KEY)
		keys->down = 1;
	else if (keycode == A_KEY)
		keys->left = 1;
	else if (keycode == D_KEY)
		keys->right = 1;
	else
		return (1);
	data->redraw = 1;
	return (0);
}
int	key_release(int keycode, t_data *data)
{
	t_keys	*keys;

	keys = &data->keys;
	if (keycode == LEFT_KEY)
		keys->turn_left = 0;
	else if (keycode == RIGHT_KEY)
		keys->turn_right = 0;
	else if (keycode == W_KEY)
		keys->up = 0;
	else if (keycode == S_KEY)
		keys->down = 0;
	else if (keycode == A_KEY)
		keys->left = 0;
	else if (keycode == D_KEY)
		keys->right = 0;
	data->redraw = 1;
	return (0);
}

