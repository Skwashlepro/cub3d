/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:56:50 by luctan            #+#    #+#             */
/*   Updated: 2025/06/03 01:19:29 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_listener(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		ft_freedata(data);
		exit(0);
	}
	else if (keycode == W_KEY)
		fwd();
	else if (keycode == A_KEY)3
		left();
	else if (keycode == S_KEY)
		right();
	else if (keycode == D_KEY)
		back();
	return (0);
}

int	on_window_close(t_data *data)
{
	ft_freedata(data);
	exit(0);
}
