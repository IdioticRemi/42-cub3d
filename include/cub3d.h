#ifndef	CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "libft.h"

# define TILE_SIZE			32
# define BUFFER_SIZE		1

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

/* DIRECTION */
# define DIR_NO				1
# define DIR_SO				2
# define DIR_WE				3
# define DIR_EA				4

/* GAME STATUS */
# define GAME_START			1
# define GAME_PLAY			2
# define GAME_CONTINUE		3
# define GAME_END			4


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
	int		floor[3];
	int		ceiling[3];
}	t_texture;

typedef struct s_map
{
	char		**array;
	int			row_count;
	int			column_count;
	t_texture	texture;
} t_map;

/*
structure for raycaster?
distance
height...

*/

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	// t_player	player;
	t_map		map;

	int			status;
} t_cub;

/* init */
void	init_game();
void	init_game_img();
void	init_mlx_and_window();
void	init_map_value();


#endif