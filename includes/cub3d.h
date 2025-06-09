/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:13:51 by luctan            #+#    #+#             */
/*   Updated: 2025/06/09 19:23:17 by lmokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define ESC_KEY 0xff1b
# define W_KEY 0x77
# define A_KEY 0x61
# define S_KEY 0x73
# define D_KEY 0x64
# include "../lib/gnl/get_next_line.h"
# include "../lib/libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_dir
{
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4,
}				t_dir;

typedef enum e_card
{
	N = 0,
	S = 1,
	W = 2,
	E = 3
}				t_card;

typedef struct s_gfx
{
	void		*wall[4];
	void		*viewmodel;
}				t_gfx;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_disp
{
	char		**map;
	void		*mlx;
	void		*mlx_win;
}				t_disp;

typedef struct s_data
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
	char		*buffer;
	char		*line;

}				t_data;

void			free_str(char *str);
int				init_map(t_data *data, char *str);
int				on_window_close(t_data *data);
void			key_listener(int keycode, t_data *data);
void			display_init(t_data *data);
void			free_map(char **map);
void			free_db(char *str, char *str2);
void			free_str(char *str);
int				check_extension(char *fichier);
int				check_player(t_data *data);
char			**copy_map(char **map);
char			**getmap(t_data *data, int fd, char **map, char *tmp);
void			ft_kill(t_data *data, int code);
void			cub_start(t_data *data);
int				check_closed(t_data *data);
int				checkwalls(t_data *data);
void			checkcardinal(t_gfx *gfx);

#endif
#endif
#endif