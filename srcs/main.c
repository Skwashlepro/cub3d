/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:10:51 by luctan            #+#    #+#             */
/*   Updated: 2025/05/15 22:08:28 by luctan           ###   ########.fr       */
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
	if (!init_map(&data, av[1])); 
		return (1);
	display_init(&data);
	ft_kill(&data);
}