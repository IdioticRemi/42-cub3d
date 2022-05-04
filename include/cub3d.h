/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:49:45 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 16:35:17 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <string.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define KEYPRESS	2
# define KEYRELEASE	3

// Constants
# define PI					3.1415926535

// GNL
# define BUFFER_SIZE		42

// Screen Size
# define SCREEN_WIDTH		1280
# define SCREEN_HEIGHT		720

// Map settings
# define TILE_SIZE			100.0
# define MINIMAP_SCALE		0.1

// Player settings
# define MOVE_SPEED			TILE_SIZE / 20
# define ROTATE_SPEED		0.04

// Camera settings
# define FOV				PI / 3
# define FOV_DEG			67

// Render settings
# define STRIP_WIDTH		1
# define STRIP_COUNT		SCREEN_WIDTH / STRIP_WIDTH
# define FOV_SHIFT			FOV / STRIP_COUNT

//Colors for tests
# define BLACK				0x00010101
# define WHITE				0x00ffffff
# define YELLOW				0x00f7d331
# define GRAY				0x00808080
# define DGRAY				0x00707070
# define RED				0x00ff4242
# define GREEN				0x0042ff42
# define BLUE				0x004298aa
# define PINK				0x00aa4298

// Keys
# define KEY_ESC			53
# define KEY_SPACE			49
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_UP				126
# define KEY_DOWN			125
# define KEY_LEFT			123
# define KEY_RIGHT			124

# define EVENT_KEY_PRESS	2
# define EVENT_EXIT			17

typedef union u_rgba
{
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
	unsigned int		value;
}	t_rgba;

typedef struct s_vect
{
	float	x;
	float	y;
}	t_vect;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_info
{
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	int		floor;
	int		ceiling;

}	t_info;

typedef struct s_map
{
	char	**array;
	char	*_array;
	int		row_count;
	int		column_count;
}	t_map;

typedef struct s_texture
{
	t_image		north;
	t_image		south;
	t_image		west;
	t_image		east;
}	t_texture;

typedef struct s_camera
{
	float		yaw;
}	t_camera;

typedef struct s_player
{
	t_vect		pos;
}	t_player;

typedef struct s_dda
{
	t_vect	vert;
	t_vect	hori;
	t_vect	offset;
	t_vect	rel_pos;
	int		map_x;
	int		map_y;
}	t_dda;

typedef struct s_keys
{
	int	key_a;
	int	key_w;
	int	key_s;
	int	key_d;
	int	key_right;
	int	key_left;
}	t_keys;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_keys		keys;
	t_info		info;
	t_image		screen;
	t_player	player;
	t_texture	texture;
	t_camera	cam;
	t_dda		dda;
	t_map		map;

}	t_cub;

// Init
void	init_game(t_cub *cub);

// GNL
int	get_next_line(int fd, char **line);

// Render
void	draw_background(t_cub *cub);
void	mlx_img_pixel_put(t_cub *cub, int x, int y, int color);
void	draw_strip(t_cub *cub, int rayID, float dist, int side);
void	put_point(t_cub *cub, t_vect coords, int color);
void	render_minimap(t_cub *cub);

// Error, exit
void	error_message_exit(char *message);
int		exit_hook(t_cub *cub);

// Free
void	free_map_arr(t_cub *cub);
void	free_char_array(char **arr);

// Map
int		map_check_file_extension(char *filename, char *ext);
void	map_read_and_check(t_cub *cub, char *map_path);
void	map_check_format(t_cub *cub);

// Event
int		key_release_event(int keycode, t_cub *cub);
int		key_press_event(int keycode, t_cub *cub);
t_vect	collision_handler(t_cub *cub);
void	rotate(t_cub *cub, float rot_angle);
void	handle_movement(t_cub *cub);

// Raycaster
void	raycaster(t_cub *cub);
float	math_map(float x, t_vect src_range, t_vect dst_range);

// Vector utils
t_vect	set_vector(float x, float y);
t_vect	vector_add(t_vect vec, t_vect to_add);
t_vect	vector_subs(t_vect vec, t_vect to_sub);
t_vect	vector_multi(t_vect vec, float num);

// Minimap
void	draw_minimap(t_cub *cub, int shift_x, int shift_y, char obstacle);
void	render_minimap(t_cub *cub);

#endif