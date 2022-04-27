#include "cub3d.h"

void	init_struct_img(t_cub *cub);

void	init_struct_texture(t_cub *cub)
{
	cub->texture.no_path = NULL;
	cub->texture.so_path = NULL;
	cub->texture.we_path = NULL;
	cub->texture.ea_path = NULL;
	cub->texture.floor = GREEN;
	cub->texture.ceiling = BLUE;
}

void	init_struct_map(t_cub *cub)
{
	cub->map.array = NULL;
	cub->map.row_count = 0;
	cub->map.column_count = 0;
}

void	init_struct_player(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.row_count)
	{
		j = 0;
		while (j < cub->map.column_count)
		{
			if (cub->map.array[i][j] == 'N'
				||cub->map.array[i][j] == 'S'
				||cub->map.array[i][j] == 'W'
				||cub->map.array[i][j] == 'E')
			{
				cub->player.start_dir = cub->map.array[i][j];
				cub->player.pos = set_vector(j, i);
			}
			j++;
		}
		i++;
	}
}

void	init_struct_fov(t_cub *cub)
{
	cub->fov.fov = 60;
	cub->fov.dir = set_fov_direction(cub);
	// cub->fov.dir = set_vector(-1, 0);
	cub->fov.plane = set_vector(0, 0.66);
	// cub->fov.plane = set_fov_plane(cub, cub->win_width);
	cub->fov.move_speed = 0.05;
	cub->fov.rot_angle = 0.05;
}

void	init_struct_cub(t_cub *cub);

void	init_struct(t_cub *cub)
{
	init_struct_texture(cub);
	init_struct_map(cub);
}