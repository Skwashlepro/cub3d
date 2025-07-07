/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:09:10 by luctan            #+#    #+#             */
/*   Updated: 2025/07/07 18:34:10 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	r;

	i = 0;
	sign = 1;
	r = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
		r = r * 10 + nptr[i++] - 48;
	if (nptr[i - 1] < '0' || nptr[i] > '9')
		return (-1);
	return (r * sign);
}

// int	main(int ac, char **av)
// {
// 	printf("%i\n", ft_atoi(av[1]));
// 	printf("%i\n", atoi(av[1]));
// }
