/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:10:51 by luctan            #+#    #+#             */
/*   Updated: 2025/06/04 19:07:55 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av, char *env[])
{
	t_data data;

	ft_memset(&data, 0, sizeof(t_data)); // memset pour gagner du temps et pas initaliser
	if (!env || !*env)
		return (1);
	else if (ac != 2)
		return (printf("INVALID ARGUMENT\n"), 0);
	if (!init_map(&data, av[1])); 
		return (1);
	display_init(&data);
	ft_kill(&data);
}
