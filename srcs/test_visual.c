#include "cub3d.h"

void	init_vis_img(t_vis *vis)
{
	vis->cub.tile.wall.ptr = mlx_xpm_file_to_image(vis->cub.mlx, "./assets_xpm/white_square32.xpm",
			&(vis->cub.tile.wall.width), &(vis->cub.tile.wall.height));
	vis->cub.tile.space.ptr = mlx_xpm_file_to_image(vis->cub.mlx, "./assets_xpm/black_square32.xpm", 
			&(vis->cub.tile.space.width), &(vis->cub.tile.space.height));
}

