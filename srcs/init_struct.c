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
	cub->map.start_dir = '\0';
}

void	init_struct_player(t_cub *cub)
{
	cub->player.x_start = 0;
	cub->player.y_start = 0;
	cub->player.pos_x = 0;
	cub->player.pos_y = 0;
}

void	init_struct_fov(t_cub *cub)
{
	cub->fov.dir_x = 0;
	cub->fov.dir_y = 0;
	cub->fov.plane_x = 0;
	cub->fov.plane_y = 0;
	cub->fov.move_speed = 0;
	cub->fov.rotate_speed = 0;
}

void	init_struct_ray(t_cub *cub);

void	init_struct_cub(t_cub *cub);
