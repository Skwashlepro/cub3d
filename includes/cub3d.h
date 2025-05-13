/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:13:51 by luctan            #+#    #+#             */
/*   Updated: 2025/05/13 18:46:09 by luctan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# ifndef WIDTH
#  ifndef HEIGHT


#   define CUB3D_H
#   define ESC_KEY 0xff1b
#   define W_KEY 0x77
#   define A_KEY 0x61
#   define S_KEY 0x73
#   define D_KEY 0x64
#   include <mlx.h>
#   include <math.h>
#   include <stdio.h>
#   include <unistd.h>
#   include <stdlib.h>

typedef	struct s_gfx
{
	void	*wall;
}	t_gfx;


typedef	struct s_player
{
	void	*viewmodel;
}	t_player;

typedef struct s_disp
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
}	t_disp;

typedef	struct s_data
{
	t_disp		display;
	t_player	p1;
	t_gfx		gfx;
}	t_data;

#  endif
# endif
#endif