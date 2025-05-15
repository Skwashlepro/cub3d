/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luctan <luctan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:13:51 by luctan            #+#    #+#             */
/*   Updated: 2025/05/15 22:06:08 by luctan           ###   ########.fr       */
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
#   include <fcntl.h>
#   include "libft.h"
#   include <stdbool.h>

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
	char		**map;
	int			fd;
	int			map_height;
	int			map_width;
	int			x;
	int			y;
	bool		error;

}	t_data;

void	free_str(char *str);
int		init_map(t_data *data, char *str);
void	key_listener();
int		on_window_close(t_data *data);
void	key_listener(int keycode, t_data *data);

#  endif
# endif
#endif