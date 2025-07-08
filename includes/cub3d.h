/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmokhtar <lmokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:13:51 by luctan            #+#    #+#             */
/*   Updated: 2025/06/11 18:37:23 by lmokhtar         ###   ########.fr       */
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
# define LEFT_KEY 0xFF51
# define RIGHT_KEY 0xFF53
# define ROT_SPEED 0.01
# define MOVE_SPEED 0.01
# define MOUSE_SENS 0.0005

# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	double			camera_x;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef enum e_card
{
	N = 0,
	S = 1,
	W = 2,
	E = 3
}					t_card;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_gfx
{
	char			*wall_path[4];
	t_img			wall[4];
	void			*viewmodel;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
}					t_gfx;

typedef struct s_keys
{
	int				left;
	int				right;
	int				up;
	int				down;
	int				turn_left;
	int				turn_right;
}					t_keys;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_disp
{
	char			**map;
	void			*mlx;
	void			*mlx_win;
}					t_disp;

typedef struct s_data
{
	t_disp			display;
	t_player		p1;
	t_gfx			gfx;
	t_img			frame;
	t_ray			ray;
	t_keys			keys;
	char			**map;
	int				fd;
	int				map_height;
	int				map_width;
	int				x;
	int				y;
	bool			error;
	char			*buffer;
	char			*line;
	int				ign_mouse;
	bool			redraw;
}					t_data;

void				free_str(char *str);
int					init_map(t_data *data, char *str);
void				display_init(t_data *data);
void				free_map(char **map);
void				free_db(char *str, char *str2);
int					check_extension(char *fichier);
int					check_player(t_data *data);
char				**copy_map(char **map);
char				**getmap(t_data *data, int fd, char **map, char *tmp);
void				ft_kill(t_data *data, int code);
void				cub_start(t_data *data);
int					check_closed(t_data *data);
int					checkwalls(t_data *data);
int					checkcardinal(t_gfx *gfx, int fd);
void				free_array(char **array);
int					valid_map(t_data *data);
int					on_window_close(t_data *data);
int					key_listener(int keycode, t_data *data);
void				map_height(char **map, int *height);
void				free_textures(int i, t_data *data);
void				clear_db(t_data *data);
void				cub_init(t_data *data);
void				rot_cam(t_data *data, double rot_speed);
int					mouse_mov(int x, int y, t_data *data);
void				movements(int keycode, t_data *data);
void				text_init(t_data *data);
int					get_texture_color(t_data *data, int tex_num, int tex_x,
						int tex_y);
void				calculate_texture_coords(t_data *data, int *tex_x,
						int *tex_y, int screen_y);
int					get_wall_texture_num(t_data *data);
int					key_release(int keycode, t_data *data);
char				**check_rgb(char *split);
int					process_cardinal(char **split, t_gfx *gfx,
						int *found_count);
void				set_init_direction(t_data *data, char dir);
void				dda(t_data *data);
int					check_texture(char **split, char **wall_texture,
						int *count);
int					check_color(char **split, unsigned int *color, int *count);
void				init_raycasting(t_data *data);
void				draw_walls(t_data *data, int x);
int					checkcardinal(t_gfx *gfx, int fd);

// # endif
#endif
