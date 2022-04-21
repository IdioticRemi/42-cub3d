#ifndef	CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <string.h>

# define GRID_SIZE			32
# define BUFFER_SIZE		1

# define PI					3.1415926535

/* COLORS FOR TESTS */
# define BLACK				0x000000
# define WHITE				0xffffff
# define YELLOW				0xf7d331
# define GRAY				0x808485
# define RED				0xff0000
# define GREEN				0xecffdc
# define BLUE				0x58cced
# define PINK				0xff69b4

/* KEYS */
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

/* GAME STATUS */
# define GAME_START			1
# define GAME_PLAY			2
# define GAME_CONTINUE		3
# define GAME_END			4

typedef struct s_vect
{
	float	x;
	float	y;
}	t_vect;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		height;
	int		width;
} t_image;

typedef struct s_texture
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_map
{
	char		**array;
	int			row_count;
	int			column_count;
} t_map;

typedef struct s_tile
{
	t_image		wall;
	t_image		exit;
	t_image		space;
} t_tile;

typedef struct s_player
{	
	char		start_dir;
	t_vect	start_grid;
	t_vect	pos;
}	t_player;

typedef struct s_fov
{
	float		x;
	float		y;
	int			fov;
	t_vect		dir;
	t_vect		plane;
	int			angle;
	float		move_speed;
	float		rot_angle;
}	t_fov;

typedef struct s_ray
{
	t_vect	dir;
	float	side_distX;
	float	side_distY;
	
	float	delta_distX;
	float	delta_distY;
	int		step_x;
	int		step_y;
	int		hit;
	int		side_hit;
	float	perpWallDist;
}	t_ray;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_texture	texture;
	t_player	player;
	t_tile		tile;
	t_fov		fov;
	t_ray		ray;
	t_map		map;
	int			status;
	int			win_height;
	int			win_width;
} t_cub;

/* init */
void	init_game();
void	init_game_img();
void	init_mlx_and_window();
void	init_map_value();

void	init_struct_img(t_cub *cub);
void	init_struct_texture(t_cub *cub);
void	init_struct_map(t_cub *cub);
void	init_struct_player(t_cub *cub);
void	init_struct_fov(t_cub *cub);
void	init_struct_ray(t_cub *cub);
void	init_struct_cub(t_cub *cub);
void	init_struct(t_cub *cub);

t_vect	set_fov_direction(t_cub *cub);
t_vect	set_fov_plane(t_cub *cub, int width);

/* get_next_line */
int	get_next_line(int fd, char **line);

/* display */
void	put_map_to_win(t_cub *cub);
void	put_player_pixel(t_cub *cub);
void	put_map_grid(t_cub *cub); //test function
void	put_player_to_win(t_cub *cub);

/* render */
void	draw_vertical_line(t_cub *cub, int x, int y1, int y2, int color);
void	put_ray(t_cub *cub);

/* error */
void	error_message_exit(char *message);

/* exit */
int		exit_hook(void);

/* free */
void	free_map_arr(t_cub *cub);

/* map */
int		map_check_file_extension(char *filename, char *ext);
void	map_read_and_check(t_cub *cub, char *map_path);
void	map_check_format(t_cub *cub);

/* event */
int		key_input(int keycode, t_cub *cub);
void	player_get_coord(t_cub *cub);
void	rotate(t_cub *cub, float rot_angle);
int	key_press(t_cub *cub, int key);

/* raycaster */
void	raycaster(t_cub *cub);

/* vector utils*/
t_vect	set_vector(float x, float y);
t_vect	vector_add(t_vect vec, t_vect to_add);
t_vect	vector_subs(t_vect vec, t_vect to_sub);
t_vect	vector_multi(t_vect vec, float num);

/* fov */
t_vect	set_fov_direction(t_cub *cub);
t_vect	set_fov_plane(t_cub *cub, int width);

#endif