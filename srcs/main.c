/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:10:51 by luctan            #+#    #+#             */
/*   Updated: 2025/06/04 19:10:30 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av, char *env[])
{
	t_data data;

	if (!env || !*env)
		return (1);
	else if (ac != 2)
		return (printf("INVALID ARGUMENT\n"), 0);
	ft_memset(&data, 0, sizeof(t_data)); // memset pour gagner du temps et pas initaliser
	if (!init_map(&data, av[1]))
		ft_kill(&data, 1);
	display_init(&data);
	ft_kill(&data, 0);
	return (0);
}
