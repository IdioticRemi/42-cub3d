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

// Constants
# define PI					3.1415926535
# define ERROR				-1

// GNL
# define BUFFER_SIZE		42

// Screen Size
# define SCREEN_WIDTH		1280
# define SCREEN_HEIGHT		720

// Map settings
# define TILE_SIZE			100.0

// Player settings
# define MOVE_SPEED			TILE_SIZE / 10
# define ROTATE_SPEED		0.1

// Camera settings
# define FOV				PI / 3
# define FOV_DEG			67

// Render settings
# define STRIP_WIDTH		8
# define STRIP_COUNT		SCREEN_WIDTH / STRIP_WIDTH
# define FOV_SHIFT			FOV / STRIP_COUNT

/* COLORS FOR TESTS */
# define BLACK				0x00010101
# define WHITE				0x00ffffff
# define YELLOW				0x00f7d331
# define GRAY				0x00808080
# define DGRAY				0x00707070
# define RED				0x00ff4242
# define GREEN				0x0042ff42
# define BLUE				0x004298aa
# define PINK				0x00aa4298

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

typedef union	u_rgba
{
	struct
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	};
	unsigned int value;
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
} t_image;

typedef struct s_info //map info 
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
	char		**array;
	char		*_array;
	int			row_count; // erase
	int			column_count; //erase
} t_map;


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
	
} t_camera;

typedef struct s_player
{
	t_vect		pos; //actual 2d position
}	t_player;

typedef struct s_dda
{
	t_vect	vert;
	t_vect	hori;
	t_vect	offset;
	t_vect	relPos;
	int		mapX;
	int		mapY;
}	t_dda;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_info		info;
	t_image		screen;
	t_player	player;
	t_texture	texture;
	t_camera	cam;
	t_dda		dda;
	t_map		map;

} t_cub;

/* init */
void	init_game();
void	init_game_img();
void	init_mlx_and_window();
void	init_map_value();

void	init_struct_img(t_cub *cub);
void	init_struct_texture(t_cub *cub);
void	init_struct_map(t_cub *cub);
void	init_struct_fov(t_cub *cub);
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
void	put_horizontal_line(t_cub *cub);

/* render */
void	draw_background(t_cub *cub);
void	mlx_img_pixel_put(t_cub *cub, int x, int y, int color);

/* error / exit */
void	error_message_exit(char *message);
int		exit_hook(t_cub *cub);

/* free */
void	free_map_arr(t_cub *cub);
void	free_char_array(char **arr);

/* map */
int		map_check_file_extension(char *filename, char *ext);
void	map_read_and_check(t_cub *cub, char *map_path);
void	map_check_format(t_cub *cub);

/* event */
int		key_input(int keycode, t_cub *cub);
void	player_get_coord(t_cub *cub);
void	rotate(t_cub *cub, float rot_angle);
int		key_press(t_cub *cub, int key);

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