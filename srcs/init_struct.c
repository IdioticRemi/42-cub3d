#include "cub3d.h"

void	init_struct_img(t_cub *cub);

void	init_struct_texture(t_cub *cub)
{
	cub->texture.no_path = NULL;
	cub->texture.so_path = NULL;
	cub->texture.we_path = NULL;
	cub->texture.ea_path = NULL;
	cub->texture.floor = 0;
	cub->texture.ceiling = 0;
}

void	init_struct_map(t_cub *cub)
{
	cub->map.array = NULL;
	cub->map.row_count = 0;
	cub->map.column_count = 0;
}

void	init_struct_player(t_cub *cub)
{
	player_get_coord(cub);
	cub->player.pos = set_vector(cub->player.start_grid.x * GRID_SIZE, cub->player.start_grid.y * GRID_SIZE);
}

void	init_struct_fov(t_cub *cub)
{
	cub->fov.dir = set_fov_direction(cub);
	cub->fov.plane = set_vector(0, 0.66);
	cub->fov.fov = 30;
	cub->fov.move_speed = 0.05;
	cub->fov.rot_angle = 0.05;
}

void	init_struct_ray(t_cub *cub);

void	init_struct_cub(t_cub *cub);

void	init_struct(t_cub *cub)
{
	init_struct_texture(cub);
	init_struct_map(cub);	
}