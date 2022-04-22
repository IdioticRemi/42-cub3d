#include "cub3d.h"

void	init_vis_img(t_vis *vis)
{
	vis->cub.tile.wall.ptr = mlx_xpm_file_to_image(vis->cub.mlx, "./assets_xpm/white_square32.xpm",
			&(vis->cub.tile.wall.width), &(vis->cub.tile.wall.height));
	vis->cub.tile.space.ptr = mlx_xpm_file_to_image(vis->cub.mlx, "./assets_xpm/black_square32.xpm", 
			&(vis->cub.tile.space.width), &(vis->cub.tile.space.height));
}

void	init_visual_win(t_vis *vis)
{
	vis->cub.win_width = SCREEN_WIDTH;
	vis->cub.win_height = SCREEN_HEIGHT;
	vis->cub.mlx = mlx_init();
	vis->cub.win = mlx_new_window(vis->cub.mlx, vis->cub.win_width, vis->cub.win_height, "visual");
}

void	init_visual(t_vis *vis)
{
	init_struct_player(&vis->cub);
	init_struct_fov(&vis->cub);
	init_visual_win(vis);
	init_vis_img(vis);

	put_map_grid(&vis->cub);
}







