/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:49:45 by selee             #+#    #+#             */
/*   Updated: 2022/05/09 12:11:30 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"
# include <mlx.h>

# define KEYPRESS	2
# define KEYRELEASE	3

// Constants
# define PI					3.1415926535
# define PI2				1.5707963267
# define PI3				1.0471975512

// Screen Size
# define SCREEN_WIDTH		1600
# define SCREEN_HEIGHT		1200

// Map settings
# define TILE_SIZE			100.0
# define MINIMAP_SCALE		0.1

// Player settings
# define MOVE_SPEED			10
# define ROTATE_SPEED		0.05

// Camera settings
# define FOV				PI3

// Render settings
# define STRIP_WIDTH		2
# define STRIP_COUNT		800
# define FOV_SHIFT			0.00130899693

//Colors
# define BLACK				0x00010101
# define WHITE				0x00ffffff
# define RED				0x00ff4242

# ifdef __linux__
// UINT64_T on Linux
#  include <bits/stdint-uintn.h>

// Movement
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307
# else
// Movement
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
# endif

// Exit

# define EVENT_EXIT			17

typedef enum e_side
{
	N,
	S,
	W,
	E
}	t_side;

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
	double	x;
	double	y;
}	t_vect;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		ln;
	int		e;
}	t_image;

typedef struct s_info
{
	char			*n_path;
	char			*s_path;
	char			*w_path;
	char			*e_path;
	unsigned int	floor;
	unsigned int	ceiling;

}	t_info;

typedef struct s_map
{
	char	**array;
	char	*_array;
	int		h;
	int		w;
}	t_map;

typedef struct s_texture
{
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
	t_rgba	n[64][64];
	t_rgba	s[64][64];
	t_rgba	w[64][64];
	t_rgba	e[64][64];
}	t_texture;

typedef struct s_camera
{
	double		yaw;
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
	int		dist;
	double	dist_vert;
	double	dist_hori;
	double	dist_final;
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

typedef struct s_strip
{
	double	d;
	int		len;
	int 	img_x;
	int		before;
	t_rgba	color;
}	t_strip;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_keys		keys;
	t_info		info;
	t_image		screen;
	t_player	player;
	t_texture	tx;
	t_camera	cam;
	t_map		map;
	char		*file;
}	t_cub;

// Init
void		init_game(t_cub *cub);
void		init_player(t_cub *cub);

// Parsing
int			read_cub_file(t_cub *cub, char *filename);
void		check_file(t_cub *cub);
int			check_texture_info(t_cub *cub, char *line);
int			check_file_extension(char *filename, char *ext);
void		check_file(t_cub *cub);
int			floodfill(char **map, int width, int height, t_vect pos);
char		*skip_spaces(char *s);
int			ft_strcnt(const char *s, char c);
int			is_number(char *s);
int			is_valid_color(const char *s);

// Render
t_side		get_side_hit(t_dda dda);
double		get_img_x(t_dda dda);
void		draw_strip(t_cub *cub, int rayID, t_dda dda);

// Error, exit
void		error_message_exit(t_cub *cub, char *message);
int			exit_hook(t_cub *cub);

// Free
void		free_map_arr(t_cub *cub);
void		free_char_array(char **arr);

// Event
int			key_release_event(int keycode, t_cub *cub);
int			key_press_event(int keycode, t_cub *cub);
t_vect		collision_handler(t_cub *cub);
void		rotate(t_cub *cub, double rot_angle);
void		handle_movement(t_cub *cub);

// Raycaster
void		get_horizontal_dist(t_cub *cub, t_dda *dda, int max_dist);
void		get_vertical_dist(t_cub *cub, t_dda *dda, int max_dist);
void		calc_horizontal(t_cub *cub, t_dda *dda, double angle, int max_dist);
void		calc_vertical(t_cub *cub, t_dda *dda, double angle, int max_dist);
void		raycaster(t_cub *cub);

// Vector utils
t_vect		set_vector(double x, double y);
t_vect		vector_add(t_vect vec, t_vect to_add);
t_vect		vector_subs(t_vect vec, t_vect to_sub);
t_vect		vector_multi(t_vect vec, double num);

// Minimap
void		put_point(t_cub *cub, t_vect coords, int color);
void		render_minimap(t_cub *cub);
void		bresenham(t_cub *cub, t_vect src, t_vect dest, int color);

// Math utils
double		math_dist(t_vect origin, t_vect arrival);

// MLX_IMAGE utils
t_rgba		mlx_img_pixel_get(t_image *img, int x, int y);
void		mlx_img_pixel_put(t_cub *cub, int x, int y, unsigned int color);

// Utils
uint64_t	ft_get_ms(void);
void		precalc_all(t_cub *cub);

#endif